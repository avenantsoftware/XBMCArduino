/*

   XBMC Arduino sketch by M.J. Meijer 2014

   control XBMC with an arduino trough JSON

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
  delay(30000);
  xbmc("Player.PlayStop","playerid\":1");
  delay(30000);
  xbmc("Player.Seek","playerid\":1,\"value\":\"smallbackward\"");
  delay(30000);
  xbmc("Player.Seek","playerid\":1,\"value\":\"smallforward\"");
  delay(30000);
  xbmc("Player.Seek","playerid\":1,\"value\":\"bigbackward\"");
  delay(30000);
  xbmc("Player.Seek","playerid\":1,\"value\":\"bigforward\"");
  delay(30000);
  xbmc("Player.SetSpeed","playerid\":1,\"speed\":\"increment\"");
  delay(30000);
  xbmc("Player.SetSpeed","playerid\":1,\"speed\":\"decrement\"");
  delay(30000);
  
  /********** navigate **********/

  xbmc("Input.ExecuteAction","action\":\"up\"");
  delay(30000);
  xbmc("Input.ExecuteAction","action\":\"down\"");
  delay(30000);
  xbmc("Input.ExecuteAction","action\":\"left\"");
  delay(30000);
  xbmc("Input.ExecuteAction","action\":\"right\"");
  delay(30000);
  xbmc("Input.ExecuteAction","action\":\"select\"");
  delay(30000);
  xbmc("Input.ExecuteAction","action\":\"back\"");
  delay(30000);

  /********** fullscreen **********/

  xbmc("GUI.SetFullscreen","fullscreen\":\"toggle\"");
  delay(30000);

  /********** subtitles **********/

  xbmc("Player.SetSubtitle","playerid\":1,\"subtitle\":\"on\"");
  delay(30000);
  xbmc("Player.SetSubtitle","playerid\":1,\"subtitle\":\"off\"");
  delay(30000);
  xbmc("Player.SetSubtitle","playerid\":1,\"subtitle\":\"next\"");
  delay(30000);
  xbmc("Addons.ExecuteAddon","addonid\":\"script.xbmc.subtitles\"");
  delay(30000);
  
  /********** language **********/

  xbmc("Player.SetAudioStream","playerid\":1,\"stream\":\"next\"");
  delay(30000);

  /********** start addons **********/

  xbmc("Addons.ExecuteAddon","addonid\":\"script.tv.show.next.aired\"");
  delay(30000);
  xbmc("Addons.ExecuteAddon","addonid\":\"plugin.video.itunes_trailers\"");
  delay(30000);
  xbmc("Addons.ExecuteAddon","addonid\":\"plugin.video.youtube\"");
  delay(30000);
  xbmc("Addons.ExecuteAddon","addonid\":\"net.rieter.xot\"");
  delay(30000);
  xbmc("Addons.ExecuteAddon","addonid\":\"script.audio.spotimc\"");
  delay(30000);

  /********** navigate menu's **********/

  xbmc("GUI.ActivateWindow","window\":\"home\"");
  delay(30000);
  xbmc("GUI.ActivateWindow","window\":\"favourites\"");
  delay(30000);
  xbmc("GUI.ActivateWindow","window\":\"weather\"");
  delay(30000);
  xbmc("GUI.ActivateWindow","window\":\"music\"");
  delay(30000);
  xbmc("GUI.ActivateWindow","window\":\"video\",\"parameters\":[\"MovieTitles\"]");
  delay(30000);
  xbmc("GUI.ActivateWindow","window\":\"video\",\"parameters\":[\"RecentlyAddedMovies\"]");
  delay(30000);
  xbmc("GUI.ActivateWindow","window\":\"video\",\"parameters\":[\"TVShowTitles\"]");
  delay(30000);
  xbmc("GUI.ActivateWindow","window\":\"video\",\"parameters\":[\"RecentlyAddedEpisodes\"]");
  delay(30000);

  /********** play music **********/

  xbmc("Player.Open","item\":{\"partymode\":\"music\"}");
  delay(30000);

  /********** select tv channel **********/

  xbmc("Player.Open","item\":{\"channelid\":41");
  delay(30000);
  xbmc("Player.Open","item\":{\"channelid\":42");
  delay(30000);
  xbmc("Player.Open","item\":{\"channelid\":43");
  delay(30000);
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
