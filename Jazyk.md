# Zposob videnia sveta #

Co vsetko moze robot vidiet
zatial -
> steny
> strela
> ostatni hraci

# Reprezentacia #

Robot vzdy vsetko vo svojom blizsie-neskor-definovanom rozsahu vidi, uzivatel sa na to moze pytat funkciou see(), ktora by mala fungovat ako pole, vracia kolko toho v dany moment vidi
**see(3) je objekt, ktory si robot vsimol az ako posledneho (objekty zoradene podla vzdialenosti, podla uhlu, (ten ktory je priamo v smere, ktorym sa robot diva,m je napadnejsi ako ten , co je niekde na pohranici vedomia, hoc aj blizsie.
Zaver - cisla oznacuju poradie botov
> \\ 1  // ...
> > \\  2/
> > > \\//**

/**TODO v pripade extremne nudenia sa - fuzziness?**

# Vlastnosti objektov #

**isPlayer() //ma to dve nohy a hybe sa**

**isMissile() strela**

**isWall()**

**isMoving() -zavisi na botovi, ak dotycny objekt videl hybat sa pred casom, blizsie definovanym vo vlastnostiach bota**

Su to vlastne prvky jazyka, raspektive objektov,
Risene samostatne az po BISONOVI

# Vlastnosti botov #

**viditelnost**

**pamat na moving**

**dostrel/rozptyl**

**pocet zivotov**

Uzivatel nema pravo vytvarat ziadne dalsie classy ani nic podobne, len cisto naprogramovat logiku, preto je to umiestnene ako samostatne prikazy jazyka

move vyhazduje int, ci sa podarilo pohnut v danom smere aleboo nie //stena a podobne

Bot ma obmedzenu pamat, musi sa kontrolovat, ci jeho pamat nie je zaplnena

Aj ked existuje trieda object, tak si ju bot nebude smiet vytvarat, ponevadz by mu bola nanic - nemoze na nu furt pouzivat is\_moving, lebo ho nemusi vidiet, dalej ma dynamicky menene pole a vidi nejaky object, moze si porovnat jeho ID, ktore je v ramci celej hry unikatne //predpoklada sa, ze neprekrocim maxint, coz je pomerne tazke