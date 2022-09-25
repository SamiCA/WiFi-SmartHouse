// biblioteke potrebne za zajednicki rad arduina i ESP8266 modula
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char ime = "Upravljanje rasvijetom"; //parametri za web pristupnu tocku
const charsifra = "12345678";
//deklaracije varijabli
const int in1=12;
int upaljeno=0;
int sklopka=2;
int s1=0;
int s2-0;
ESP8266WebServer server (80); // nacin rada kao web poslužitelj
void handleRoot()
// kada klijent zatrazi adresu 192.168.4.1 otvara se web stranica za prijavu
{
  server.send (200, "text/html", "<meta content='width=device-width, initial-scale=1' name='viewport'/><form action="/login" method="POST"><input type="text" name="username" placeholder="Korisnicko ime"></br><input type="password" name="password" placeholder="Zaporka"></br><input type="submit\"value="Prijava"></form>");
} 
void handleLogin()
{
  if(! server.hasArg ("username")  || ! server.hasArg("password") || server.arg("username") == NULL || server.arg("password") == NULL)
  {
  server.send(400, "text/plain", "400: Zahtjev nije ispravan");
  }
  return;
}
if(server.arg("username") == "Sami" && server.arg("password") == "1234") // Ukoliko su korektni korisnicko ime i lozika otvara se web stranica izbornika
{ 
  server.send(200, "text/html", "<meta content='width=device-width, initial-scale=1' name='viewport'/><h1>Dobrodosao/la, " + server.arg("username") + "<meta content='width=device-width, initial-scale=1' name='viewport'/>!</h1> <p>Prijava uspjesna</p> <form action="/IZBORNIK" method="POST"><input type="submit" value="Kuhinja"></form><input type="submit" value="Boravak"><p><input type="submit" value="Toalet"></p>");
}
else
{
  server.send(401, "text/plain", "401: Pogresno korisnicko ime i lozinka"); //Ukoliko se ne poklapaju korisnicko ime ili lozinka klijent dobija sljedecu poruku
}
void handleSVJETLO() 
{
  digitalWrite(in1,!digitalRead(in1));
  server.sendHeader("Location", "/IZBORNIK");
  server.send(303);
}
void handlepLogin()
{
  if (digitalRead (in1) == HIGH) 
  {
  // Ukoliko je stanje releja "HIGH" (logicka 1/5V) ispisuje nam da je svjetlo upaljeno, a gumb da ga mozemo ugasit
    server.send(200, "text/html","<meta content='width=device-width, initial-scale=1' name='viewport'/><h1>Svjetlo je upaljeno<form id='F1' action='SVJETLO'><input class='button' type='submit' value='Ugasi svjetlo' ></form> <br>");
    upaljeno=1;
  }
  else
  {
    // Isto kao i predhodan komentar osim toga sto su parametri obrnuti
    server.send(200, "text/html","<meta content='width=device-width, initial-scale=1' name='viewport'/><h1>Svjetlo je ugaseno<form id='F1' action='SVJETLO'><input class='button' type='submit' value='Upali svjetlo' ></form> <br>");
    upaljeno=0;
  }
}
void setup()
{
  delay(1000);
  Serial.begin(115200);
  WiFi.softAP (ime, sifra);
  pinMode(in1, OUTPUT);
  pinMode(sklopka, INPUT);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println("IP adresa pristupne tocke: ");
  Serial.println(myI?);
  server.on("/", handleRoot); // Ukoliko korisnik zatrazi adresu 192.168.4.1 poziva se web stranica "handleRoot"
  server.on("/login", handleLogin); // Ukoliko korisnik zatrazi adresu 192.168.4.1/login poziva se web stranica "handleLogin"
  server.on("/IZBORNIK", handlepLogin); // Ukoliko korisnik zatrazi adresu 192.168.4.1/IZBORNIK poziva se web stranica "handlepLogin" (pLogin skraćenica za post Login kao proces koji se obavlja nakon prijave)
  server.on("/SVJETLO", handleSVJETLO); // Ukoliko korisnik zatrazi adresu 192
  server.begin();
  Serial.println("HTTP server pokrenut");
}
void loop()
{
  // ocitava stanje sklopke
  s1 = digitalRead(2);
  // usporedjuje je s predhodnim stanjem
  if (s1 != s2) 
  {
    if (s1 == HIGH) 
    {
      Serial.println("on");
      delay(50);
      s2 = s1; // Drugo stanje je sada prvo kako bi se petlja mogla nastavit održavat
    }
    digitalWrite(in1,!digitalRead(in1));
    Serial.print("number of button pushes: "); //debug
  } 
  else 
  {
    digitalWrite(in1,!digitalRead(in1));
    Serial.println("off"); 
  }
  delay(50); 
  s2 = s1; // Drugo stanje je sada prvo kako bi se petlja mogla nastavit održavat
  Serial.println("off");
  delay (60);
  server.handleClient(); // provodi zahtjeve klijenta
}