//
// Created by roanr on 14/01/2025.
//

#include "base.h"
#include "assert.h"
#include "calculator.h"
#include "functionWindow.h"
#include "keyboardWindow.h"
#include "menu.h"
#include "variableWindow.h"
#include <QApplication>
#include <QLabel>
#include <QListWidget>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <qnamespace.h>
#include <sstream>

using namespace gui;

base::base(QWidget *parent)
    : QMainWindow(parent), centralWidget(new QWidget(this)),
      layout(new QGridLayout()),
      calc(std::make_unique<calculator::Calculator>()),
      quitButton(new QPushButton("quit", this)),
      treeButton(new QPushButton("tree output", this)),
      evaluateButton(new QPushButton("=", this)),
      logButton(new QPushButton("log", this)),
      functionButton(new QPushButton("functions", this)),
      resetButton(new QPushButton("reset", this)),
      keyboardButton(new QPushButton("keyboard", this)),
      variableButton(new QPushButton("variables", this)),
      writeButton(new QPushButton("write to file", this)),
      selectFile(new QComboBox(this)),
      last_operation(new QLabel("None\n\n\n\n", this)),
      evaluateBox(new QLineEdit(this)), keyboard(new keyboardWindow()),
      functions(new functionWindow()), variables(new variableWindow()) {
  QWidget::setWindowTitle("Main window");
#if not __linux__
  treeButton->setDisabled(true);
#endif
  // setFixedSize(500,500);
  // quitButton->setPalette(QPalette(QColor("White")));
  setWindowFlags(Qt::Window | Qt::WindowTitleHint);
  layout->addWidget(quitButton, 0, 3,1,2);
  layout->addWidget(keyboardButton, 3, 1,1,2);
  layout->addWidget(resetButton, 0,1, 1,2);
  layout->addWidget(evaluateBox, 6, 1, 1, 3);
  layout->addWidget(evaluateButton, 6, 4);
  layout->addWidget(treeButton, 1, 3,1,2);
  layout->addWidget(logButton, 1, 1);
  layout->addWidget(functionButton, 3, 3, 1, 1);
  layout->addWidget(variableButton, 3, 4, 1, 1);
  layout->addWidget(last_operation, 5, 2, 1, 3);
  layout->addWidget(selectFile, 2, 1,1,4);
  layout->addWidget(writeButton, 1, 2);
  layout->addWidget(new QLabel("Last Operation:\n\n\n\n", this), 5, 1);
  list = new QListWidget(this);
  layout->addWidget(list, 4, 1, 1, 4);
  auto basefuncs = calc->_mem->_funcs;
  functions->add_base(basefuncs);
  auto basevars = calc->_mem->_gvars;
  variables->add_base(basevars);
  centralWidget->setLayout(layout);
  setCentralWidget(centralWidget);
    QPixmap bkgnd("guimages/img_1.png");
    //bkgnd = bkgnd.scaled(QSize(1077,808));
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
  show();
  files();
  /*for(int i=0;i<layout->count();i++){
      layout->itemAt(i)->widget()->setPalette(QPalette(QColor("lightGray")));
  }*/
  std::vector<string> resetvector = {"reset", "cancel"};
  resetmenu =
      new menu("Are you sure you want to reset? This action can't be undone",
               resetvector);
  std::vector<string> writevector = {"write", "cancel"};
  writemenu = new menu("Enter filename:", writevector, false, true);
  connect(resetmenu->buttons[0], SIGNAL(clicked()), this, SLOT(reset()));
  connect(resetmenu->buttons[1], SIGNAL(clicked()), this, SLOT(cancel()));
  connect(writemenu->buttons[0], SIGNAL(clicked()), this, SLOT(preWrite()));
  connect(writemenu->buttons[1], SIGNAL(clicked()), this, SLOT(cancel()));
  connect(quitButton, SIGNAL(clicked()), QApplication::instance(),
          SLOT(quit()));
  connect(evaluateButton, SIGNAL(clicked()), this, SLOT(evaluate()));
  connect(writeButton, SIGNAL(clicked()), this, SLOT(openWriteMenu()));
  connect(keyboard->evaluate, SIGNAL(clicked()), this, SLOT(evaluate()));
  connect(resetButton, SIGNAL(clicked()), this, SLOT(openResetMenu()));
  connect(functionButton, SIGNAL(clicked()), this, SLOT(getFunctions()));
  connect(logButton, SIGNAL(clicked()), this, SLOT(log()));
  connect(keyboardButton, SIGNAL(clicked()), this, SLOT(getKeyboard()));
  connect(treeButton, SIGNAL(clicked()), this, SLOT(openTreeMenu()));
  connect(variableButton, SIGNAL(clicked()), this, SLOT(getVariables()));
  connect(keyboard->clear, SIGNAL(clicked()), evaluateBox, SLOT(clear()));
  connect(keyboard, &keyboardWindow::character_signal, this, &base::addChar);
  connect(keyboard->backspace, SIGNAL(clicked()), this, SLOT(backspace()));
  connect(functions, &functionWindow::addToExpr, this, &base::addToExpr);
  connect(variables, &variableWindow::addToExpr, this, &base::addToExpr);
  connect(functions, &functionWindow::newfunc, this, &base::execute);
  connect(variables, &variableWindow::newVariable_signal, this, &base::execute);
  connect(selectFile, SIGNAL(currentIndexChanged(int)), this,
          SLOT(loadFile(int)));
  connect(this, &base::variable_success, variables, &variableWindow::newvaradd);
  connect(this, &base::function_success, functions,
          &functionWindow::newfuncadd);
  keyboard->setHidden(true);
}

base::~base() { log(); }

void base::addexpr(const std::string &expression) {
  std::string thing = expression;

  while (thing[thing.size() - 1] == '0') {
    thing.pop_back();
  }
  if (thing[thing.size() - 1] == '.') {
    thing.pop_back();
  }

  list->addItem(thing.c_str());
}

void base::evaluate() {
  QString thing = evaluateBox->text();
  execute(thing.toStdString());
}

void base::addChar(char c) {
  QString text = evaluateBox->text();
  text.push_back(c);
  evaluateBox->setText(text);
}

void base::getKeyboard() { keyboard->setHidden(keyboard->isVisible()); }

void base::backspace() {
  std::string text = evaluateBox->text().toStdString();
  text.pop_back();
  evaluateBox->setText(text.c_str());
}

void base::reset() {
  enableall();
  resetmenu->hide();
  list->clear();
  auto newthing = std::make_unique<calculator::Calculator>();
  calc.swap(newthing);
  auto basefuncs = calc->_mem->_funcs;
  functions->add_base(basefuncs);
  auto basevars = calc->_mem->_gvars;
  variables->add_base(basevars);
  evaluateBox->clear();
  last_operation->setText("None\n\n\n\n");
  files();
  log();
  current_log.clear();
  outtoin.clear();
  astbyinput.clear();
  ptbyinput.clear();
}

void base::getFunctions() { functions->setHidden(functions->isVisible()); }

void base::addToExpr(std::string f) {
  std::string text = evaluateBox->text().toStdString();
  text += f;
  evaluateBox->setText(text.c_str());
}

void base::getVariables() { variables->setHidden(variables->isVisible()); }

void base::update_last(int type, string result, string input) {
  string operationstring;
  operationstring += "Input: " + input + "\n";
  operationstring += "Operation type: ";
  std::string full;
  switch (type) {
  case 2:
    operationstring += "Expression";
    full = input + " = " + result;
    addexpr(full);
    outtoin[full] = input;
    break;
  case 3:
    operationstring += "Function Assignment";
    full = input;
    addexpr(full);
    outtoin[full] = input;
    emit function_success(input);
    break;
  case 4:
    operationstring += "Variable Assignment";
    full = input + " = " + result;
    addexpr(full);
    outtoin[full] = input;
    emit variable_success(input, result);
    break;
  default:
    if (input.find('=') == string::npos) {
      operationstring += "probably an expression";
    } else if (input.substr(0, input.find('=')).find('(') != string::npos ||
               input.substr(0, input.find('=')).find(')') != string::npos) {
      operationstring += "probably a function assignment";
    } else {
      operationstring += "probably a variable assignment";
    }
  }
  operationstring += "\nSuccess: ";
  switch (type) {
  case 0:
    operationstring += "false\n";
    operationstring += "Error: There was an error in parsing\n";
    operationstring += "Message: " + result;
    break;
  case 1:
    operationstring += "false\n";
    operationstring += "Error: Expression invalid\n";
    operationstring += "Message: " + result;
    break;
  case 2:
    operationstring += "true\n";
    operationstring += "Result: " + result;
    break;
  case 3:
    operationstring += "true\n";
    operationstring +=
        "Result: function \"" + input.substr(0, input.find('(')) + "\" added";
    break;
  default:
    operationstring += "true\n";
    operationstring +=
        "Result: variable \"" + input.substr(0, input.find('=')) + "\" added";
    operationstring += "\nValue: " + result;
  }
  int amount = std::count(operationstring.begin(), operationstring.end(), '\n');
  for (int i = 0; i < 4 - amount; i++) {
    operationstring += '\n';
  }
  last_operation->setText(operationstring.c_str());
  current_log.push_back(operationstring);
}

void base::execute(string f) {
  auto res = calc->enterOperation(f);
  string result = res->_message;
  astbyinput[f] = res->_ast;
  ptbyinput[f] = res->_parseTree;
  update_last(int(res->_type), result, f);
}

void base::files() {
  selectFile->clear();
  selectFile->addItem("select a file");
  selectFile->addItem("update selection");
  selectFile->setCurrentIndex(0);
  for (const auto &entry : std::filesystem::directory_iterator("files")) {
    auto filename = entry.path().filename().generic_string();
    const char *filecstr = filename.c_str();
    selectFile->addItem(filecstr);
    string pad = entry.path().generic_string();
    filenames.push_back(pad);
  }
}

void base::loadFile(int index) {
  if (index < 1) {
    return;
  }
  if (index == 1) {
    files();
    return;
  }
  selected = index;
  disableall();
  std::vector<string> optionsvector = {"load", "load & reset", "cancel"};
  filemenu = new menu("Select an option for file \"" +
                          filenames[selected - 2].substr(6) + "\"",
                      optionsvector);
  connect(filemenu->buttons[0], SIGNAL(clicked()), this, SLOT(load()));
  connect(filemenu->buttons[1], SIGNAL(clicked()), this, SLOT(loadAndReset()));
  connect(filemenu->buttons[2], SIGNAL(clicked()), this, SLOT(cancel()));
  selectFile->setCurrentIndex(0);
  filemenu->show();
}

void base::loadAndReset() {
  enableall();
  delete filemenu;
  filemenu = nullptr;
  reset();
  load();
}

void base::load() {
  enableall();
  delete filemenu;
  filemenu = nullptr;
  std::ifstream base(filenames[selected - 2]);
  if (!base.is_open()) {
    return;
  }
  std::string line;
  while (std::getline(base, line)) {
    execute(line);
  }
}

void base::cancel() {
  enableall();
  delete filemenu;
  filemenu = nullptr;
  resetmenu->setHidden(true);
  writemenu->setHidden(true);
  writemenu->textBox->clear();
  delete overwritemenu;
  overwritemenu = nullptr;
  delete treemenu;
  treemenu = nullptr;
}

void base::disableall() {
  keyboard->setDisabled(true);
  functions->setDisabled(true);
  variables->setDisabled(true);
  centralWidget->setDisabled(true);
}

void base::enableall() {
  keyboard->setDisabled(false);
  functions->setDisabled(false);
  variables->setDisabled(false);
  centralWidget->setDisabled(false);
}

void base::openResetMenu() {
  resetmenu->show();
  disableall();
}

void base::write() {
  std::string filename = writemenu->textBox->text().toStdString();
  filename = "files/" + filename + ".txt";
  enableall();
  std::ofstream writetofile(filename);
  std::string output_string;
  for (int i = 0; i < list->count(); i++) {
    string current = list->item(i)->text().toStdString() + "\n";
    if (std::count(current.begin(), current.end(), '=') == 2) {
      string second_part = current.substr(current.find('=') + 1);
      second_part = second_part.substr(second_part.find('='));
      output_string += current.substr(0, current.find('=')) + second_part;
      continue;
    }
    output_string += current;
  }
  writetofile << output_string << std::endl;
  writetofile.close();
  writemenu->hide();
  writemenu->textBox->clear();
  delete overwritemenu;
  overwritemenu = nullptr;
}

void base::openWriteMenu() {
  writemenu->show();
  disableall();
}

void base::preWrite() {
  std::string filename = writemenu->textBox->text().toStdString();
  if (filename.empty()) {
    writemenu->textBox->setText("Please enter a filename");
    return;
  } else if (filename.find(' ') != string::npos) {
    writemenu->textBox->setText("Please enter a valid filename");
    return;
  }
  filename = "files/" + filename + ".txt";
  if (std::filesystem::exists(filename)) {
    overwritemenu = new menu("are you sure you want to overwrite file \"" +
                                 filename.substr(6) + "\"?",
                             {"yes", "no"});
    connect(overwritemenu->buttons[0], SIGNAL(clicked()), this, SLOT(write()));
    connect(overwritemenu->buttons[1], SIGNAL(clicked()), this,
            SLOT(overwriteCancel()));
    overwritemenu->show();
    writemenu->setDisabled(true);
    return;
  }
  write();
}

void base::overwriteCancel() {
  delete overwritemenu;
  overwritemenu = nullptr;
  writemenu->setDisabled(false);
}

void base::log() {
  time_t timestamp;
  time(&timestamp);
  std::string filename = "logs/log_";
  filename += ctime(&timestamp);
  filename.pop_back();
  filename += ".txt";
  std::replace(filename.begin(), filename.end(), ' ', '_');
  std::replace(filename.begin(), filename.end(), ':', '-');
  std::ofstream writetofile(filename);
  std::string output_string;
  for (const string &line : current_log) {
    output_string += line + "\n\n";
  }
  if (output_string.empty()) {
    output_string = "nothing happened";
  }
  writetofile << output_string << std::endl;
  writetofile.close();
  QWidget *text = new QLabel(output_string.c_str());
  outputs.push_back(text);
  text->show();
  text->setWindowTitle(filename.substr(5).c_str());
}

template <typename TREE_T>
inline auto createPNG(const string &dotfile, const string &pngfile,
                      const TREE_T &root) {
  GraphvizTool gt{};
  gt.createDotFile(dotfile, root);

  auto command = "dot -Tpng " + dotfile + " > " + pngfile;
  auto commandcstr = command.c_str();

  std::system(commandcstr);

  auto image = new QPixmap();
  image->load(pngfile.c_str());
  auto imlabel = new QLabel();
  imlabel->setPixmap((*image).scaled(std::min(1000, image->width()),
                                     std::min(1000, image->height()),
                                     Qt::KeepAspectRatio));
  imlabel->show();

  return imlabel;
};

void base::tree(QListWidgetItem *item) {
  enableall();
  string input = outtoin[item->text().toStdString()];
  auto ast = astbyinput[input];
  auto pt = ptbyinput[input];
  time_t timestamp;
  time(&timestamp);

  std::string prefix = "output/graph_";
  prefix += ctime(&timestamp);
  prefix.pop_back();
  std::replace(prefix.begin(), prefix.end(), ' ', '_');
  std::replace(prefix.begin(), prefix.end(), ':', '-');

  string ast_dotfilename = prefix + "_AST.txt";
  string pt_dotfilename = prefix + "_PT.txt";
  string ast_pngfilename = prefix + "_AST.png";
  string pt_pngfilename = prefix + "_PT.png";

  outputs.push_back(createPNG(ast_dotfilename, ast_pngfilename, ast));
  outputs.push_back(createPNG(pt_dotfilename, pt_pngfilename, pt));

  treemenu->hide();
}

void base::openTreeMenu() {
  disableall();
  std::vector<string> options;
  for (int i = 0; i < list->count(); i++) {
    options.push_back(list->item(i)->text().toStdString());
  }
  treemenu = new menu("select a line (double click)", options, true);
  connect(treemenu->list, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this,
          SLOT(tree(QListWidgetItem *)));
  connect(treemenu->buttons[0], SIGNAL(clicked()), this, SLOT(cancel()));
  treemenu->show();
}
// gui
