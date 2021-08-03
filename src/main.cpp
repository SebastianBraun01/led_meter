#include <Arduino.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>
#include "Secret.h"   // Ich will meine WLAN Zugangsdaten nicht veröffentlichen


// Netzwerkdaten damit sich Blynk über WLAN verbinden kann ========================================
char auth[] = secret_auth_sound;     // Code für Verstärker
char ssid[] = secret_ssid;
char pass[] = secret_pass;


// Initialisierung für globale Variablen und Objekte ==============================================
WidgetTerminal terminal(V3);
WidgetBridge bridge_wand(V10);
WidgetBridge bridge_lounge(V11);

int pegel = 0;


// ================================================================================================
void setup() {
  analogReadResolution(12);

  // Initialisierung von Blynk
  Blynk.begin(auth, ssid, pass);
  while(Blynk.connected() == false);
  terminal.clear();
  terminal.println("Musik-Server gestartet!");
  terminal.flush();
}


void loop() {
  pegel = analogRead(A0);
  bridge_wand.virtualWrite(V10, pegel);
  bridge_lounge.virtualWrite(V11, pegel);
  Blynk.run();
}


BLYNK_CONNECTED() {
  bridge_wand.setAuthToken(secret_auth_wand);
  bridge_lounge.setAuthToken(secret_auth_lounge);
}
