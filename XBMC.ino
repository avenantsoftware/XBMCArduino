/*

   XBMC/Kodi Arduino sketch by M.J. Meijer 2014

   control XBMC with an arduino through JSON

   disable password and username in xbmc

*/

#include <SPI.h>
#include <Ethernet.h>

// arduino mac address
byte mac[] = {0xDE,0xAC,0xBF,0xEF,0xFE,0xAA};

// xbmc ip
byte xbmchost[] = {192,168,2,3};


EthernetClient client;

void setup()
{
  Serial.begin(9600);
  Serial.print(F("Starting ethernet..."));
  if(!Ethernet.begin(mac)) Serial.println("failed");
  else Serial.println(Ethernet.localIP());

  delay(5000);
  Serial.println("Ready");
}

void loop()
{
  /********** media buttons **********/
  
  xbmc("Player.PlayPause","playerid\":1");
  delay(2000);
  xbmc("Player.Stop","playerid\":1");
  delay(2000);
  xbmc("Player.Seek","playerid\":1,\"value\":\"smallbackward\"");
  delay(2000);
  xbmc("Player.Seek","playerid\":1,\"value\":\"smallforward\"");
  delay(2000);
  xbmc("Player.Seek","playerid\":1,\"value\":\"bigbackward\"");
  delay(2000);
  xbmc("Player.Seek","playerid\":1,\"value\":\"bigforward\"");
  delay(2000);
  xbmc("Player.SetSpeed","playerid\":1,\"speed\":\"increment\"");
  delay(2000);
  xbmc("Player.SetSpeed","playerid\":1,\"speed\":\"decrement\"");
  delay(2000);
  
  /********** navigate **********/

  xbmc("Input.ExecuteAction","action\":\"up\"");
  delay(2000);
  xbmc("Input.ExecuteAction","action\":\"down\"");
  delay(2000);
  xbmc("Input.ExecuteAction","action\":\"left\"");
  delay(2000);
  xbmc("Input.ExecuteAction","action\":\"right\"");
  delay(2000);
  xbmc("Input.ExecuteAction","action\":\"select\"");
  delay(2000);
  xbmc("Input.ExecuteAction","action\":\"back\"");
  delay(2000);

  /********** fullscreen **********/

  xbmc("GUI.SetFullscreen","fullscreen\":\"toggle\"");
  delay(2000);

  /********** subtitles **********/

  xbmc("Player.SetSubtitle","playerid\":1,\"subtitle\":\"on\"");
  delay(2000);
  xbmc("Player.SetSubtitle","playerid\":1,\"subtitle\":\"off\"");
  delay(2000);
  xbmc("Player.SetSubtitle","playerid\":1,\"subtitle\":\"next\"");
  delay(2000);
  xbmc("Addons.ExecuteAddon","addonid\":\"script.xbmc.subtitles\"");
  delay(2000);
  
  /********** language **********/

  xbmc("Player.SetAudioStream","playerid\":1,\"stream\":\"next\"");
  delay(2000);

  /********** start addons **********/

  xbmc("Addons.ExecuteAddon","addonid\":\"script.tv.show.next.aired\"");
  delay(2000);
  xbmc("Addons.ExecuteAddon","addonid\":\"plugin.video.itunes_trailers\"");
  delay(2000);
  xbmc("Addons.ExecuteAddon","addonid\":\"plugin.video.youtube\"");
  delay(2000);
  xbmc("Addons.ExecuteAddon","addonid\":\"net.rieter.xot\"");
  delay(2000);
  xbmc("Addons.ExecuteAddon","addonid\":\"script.audio.spotimc\"");
  delay(2000);
  
  /********** enable/disable addons **********/
  
  xbmc("Addons.SetAddonEnabled","addonid\":\"script.xbmc.boblight\",\"enabled\":true");
  delay(5000)
  xbmc("Addons.SetAddonEnabled","addonid\":\"script.xbmc.boblight\",\"enabled\":false");
  delay(5000)

  /********** navigate menu's **********/

  xbmc("GUI.ActivateWindow","window\":\"home\"");
  delay(2000);
  xbmc("GUI.ActivateWindow","window\":\"favourites\"");
  delay(2000);
  xbmc("GUI.ActivateWindow","window\":\"weather\"");
  delay(2000);
  xbmc("GUI.ActivateWindow","window\":\"music\"");
  delay(2000);
  xbmc("GUI.ActivateWindow","window\":\"video\",\"parameters\":[\"MovieTitles\"]");
  delay(2000);
  xbmc("GUI.ActivateWindow","window\":\"video\",\"parameters\":[\"RecentlyAddedMovies\"]");
  delay(2000);
  xbmc("GUI.ActivateWindow","window\":\"video\",\"parameters\":[\"TVShowTitles\"]");
  delay(2000);
  xbmc("GUI.ActivateWindow","window\":\"video\",\"parameters\":[\"RecentlyAddedEpisodes\"]");
  delay(2000);

  /********** play music **********/

  xbmc("Player.Open","item\":{\"partymode\":\"music\"}");
  delay(2000);

  /********** select tv channel **********/

  xbmc("Player.Open","item\":{\"channelid\":41");
  delay(2000);
  xbmc("Player.Open","item\":{\"channelid\":42");
  delay(2000);
  xbmc("Player.Open","item\":{\"channelid\":43");
  delay(2000);
}

/*********** Send XBMC JSON **********/

void xbmc(char *method, char *params)
{
  if (client.connect(xbmchost,8090))
  {
    client.print("GET /jsonrpc?request={\"jsonrpc\":\"2.0\",\"method\":\"");
    client.print(method);
    client.print("\",\"params\":{\"");
    client.print(params);
    client.println("},\"id\":1}  HTTP/1.1");
    client.println("Host: XBMC");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
  else
  {
    client.stop();
  }
}
