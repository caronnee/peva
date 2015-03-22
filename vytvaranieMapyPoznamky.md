uzivatelsky prijemne vytvaranie mapy:


chcelo byt to, aby ked clovek drzi mys, pokracovalo  kladenie stien, ale potom je
- vela stien, co nie je taky problem, odstranime prekryvajuce sa
-

problemy, ktore mozu nastat pri prekryvani stien:
- colizia s pushStenou - pokial pushStenu nieco preskryvam potom sa jej zacne preskakovat pixelova hodnota
- kolizia s trapstenou - OK
- kolizia s START -not OK, tie by sa preryvat nemali
- kolizia so solidWall - ok
- kolizia s breakable wall- not ok

---

riesenie toho, ze budeme stelovat mys:
najdme posledne, co sme vlozili (x1, y1), najdeme, kde sme teraz (x2,y2), zistime, kolko stien sa zmesti zvrchu a zboku (a, b), chceme to maximum, co tam natrepeme
-museli by sme klonovat, pretoze ide o virtualne riedy, zaklad objekt