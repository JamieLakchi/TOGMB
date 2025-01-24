# TOg Machines en Berekenbaarheid (groep 8)
## Wetenschappelijk rekenblad
## Dependencies

- cmake
- c++17 compiler
- qt5 base
- graphviz cli (voor parse tree en AST visualisatie)

***Als de std::to_string implementatie kommas gebruikt in plaats van punten, kunnen problemen optreden.***

## Gebruik 
### Rekenen

Simpele rekenoperaties uitvoeren:

![](https://github.com/JamieLakchi/TOGMB/blob/master/READMEImages/rekenkunde.png)

### Variabelen 

Uitkomsten opslaan:

![](https://github.com/JamieLakchi/TOGMB/blob/master/READMEImages/vars.png)

### Functies 

Nieuwe functies aanmaken:

![](https://github.com/JamieLakchi/TOGMB/blob/master/READMEImages/funcs.png)

### Errors

Een voorbeeld log:

![](https://github.com/JamieLakchi/TOGMB/blob/master/READMEImages/log.png)

### (opt) Visualisatie 

Parse tree en AST (van "sqrtandsomemore(x) = pow(x,0.5) + sin(x) + cos(x) - log(e,x)"):

![](https://github.com/JamieLakchi/TOGMB/blob/master/READMEImages/PT.png)
![](https://github.com/JamieLakchi/TOGMB/blob/master/READMEImages/AST.png)

### Other

Verder is het mogelijk om een toestand op te slaan of in te laden via de 'write to file'- en 'select a file'-knoppen, en om alle variabelen en functies in het geheugen te bekijken via de 'functions'- en 'variables'-knoppen.
