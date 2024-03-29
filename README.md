# FIT-PA2-Polynomials

This is a project created as a homework for subject Programming and algorithmic 2 (BI-PA2 - Programování a algoritmizace 2) at FIT CTU.

Full assignment in Czech language is below.

Summary of the assignment: Create C++ class that will represent polynomials.

---

Basically, the point of this assignment is to use operator overload in C++.

My solution is in file `solution.cpp`, function main of this file contains test data for basic scenarios.

My solution has received 5 points out of 5, which is maximum.

# Assignment

Úkolem je realizovat třídu `CPolynomial`, která bude reprezentovat polynomy.

Třída `CPolynomial` ukládá polynom pomocí koeficientů u jednotlivých jeho mocnin. Předpokládáme koeficienty v podobě desetinných čísel typu `double`. Pomocí rozhraní (většina rozhraní má podobu přetížených operátorů) dokáže tato třída s polynomy pracovat. Realizovaná třída musí splňovat následující rozhraní:

- **konstruktor implicitní**
inicializuje objekt, který bude reprezentovat polynom o hodnotě 0.

- **kopírující konstruktor**
bude implementován, pokud to vnitřní struktury Vaší třídy vyžadují.

- **destruktor**
bude implementován, pokud to vnitřní struktury Vaší třídy vyžadují.

- **přetížený operátor =**
bude umožňovat kopírování polynomů (pokud automaticky generovaný operátor = nevyhovuje).

- **operátor <<**
bude umožňovat výstup objektu do C++ streamu. Výpis bude realizován v kompaktní podobě:
  - členy jsou zobrazované směrem od nejvyšší mocniny,
  - členy s nulovým koeficientem nebudou zobrazované,
  - členy s koeficientem `+1` či `-1` nebudou zobrazovat číslo 1, zobrazí pouze příslušnou mocninu x,
  - ve výpisu nejsou zbytečná znaménka - (tedy např. `x^1 - 9` nebo `- x^2 + 4` je správné, ale `x^1 + (-9)` je špatně),
  - nulový polynom se zobrazí jako samostatné číslo 0.

  Výchozí proměnnou v zobrazovaném polynomu bude proměnná `x`. Manipulátorem půjde jméno proměnné změnit (bonusové rozšíření).

- **operátor +**
umožní sečíst dva polynomy,

- **operátor -**
umožní odečíst dva polynomy,

- **operátor \***
umožní vynásobit polynom desetinným číslem nebo dva polynomy,

- **operátory == a !=**
umožní porovnat polynomy na přesnou shodu,

- **operátor []**
umožní nastavit/zjistit hodnotu koeficientu u zadané mocniny polynomu. Čtecí varianta musí fungovat i pro konstantní polynomy,

- **operátor ()**
umožní vyhodnotit hodnotu polynomu pro zadanou hodnotu x (x je desetinné číslo),

- **Degree()**
metoda zjistí stupeň polynomu (např. `x^3+4` má stupeň 3, 5 má stupeň 0, 0 má stupeň 0).

- **manipulátor polynomial_variable( name )**
Manipulátorem půjde změnit proměnná, kterou bude zobrazovat výstup do streamu. Nebude-li manipulátor použit, zobrazí se polynom s proměnnou x. Pokud manipulátor použijeme, změní se proměnná v zobrazeni polynomu na zadaný řetězec. Toto rozšíření je testované pouze v bonusových testech. Pokud se jím nechcete zabývat, ponechte ukázkové deklarace `polynomial_variable` beze změn (dodaná implementace manipulátoru nic nedělá, manipulátor lze použít a program lze zkompilovat).

Odevzdávejte zdrojový soubor, který obsahuje Vaší implementaci třídy `CPolynomial`. V odevzdávaném souboru nenechávejte vkládání hlavičkových souborů, Vaše testovací funkce a funkci `main`. Pokud v souboru chcete ponechat main nebo vkládání hlavičkových souborů, vložte je do bloku podmíněného překladu.

V tomto příkladu není poskytnutý přesný předpis pro požadované rozhraní třídy. Z textového popisu, ukázky použití v příloze a ze znalostí o přetěžování operátorů byste měli být schopni toto rozhraní vymyslet.
