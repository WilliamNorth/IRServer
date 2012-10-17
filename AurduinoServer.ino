/*
 * Arduino Custom Command Server (via the virtual serial port) "ArduinoServer.ino".
 * License: GPL
 * 
 * This is the Arduino Server sketch "ArduinoServer.ino".
 * Configure the Serial Monitor to send a 'Newline' when the [Enter] key is pressed 
 * or the 'Send' button is clicked, and set the rate to 115200 baud.
 * 
 * This server is setup to run the IRServer application "IRServerApp.ino".
 */

#define SERVER_NAME       "Arduino Custom Command Server"
#define SERVER_VERSION    0.28
#define SERVER_DATE       "2012-10-16"
#define SERVER_COPYRIGHT  "Copyright (C) 2012 William North"

void displayServerSplash()
{
  Serial.print(SERVER_NAME);
  Serial.print(" version ");
  Serial.print(SERVER_VERSION);
  Serial.print(" of ");
  Serial.print(SERVER_DATE);
  Serial.print(" ");
  Serial.println(SERVER_COPYRIGHT); 
  Serial.print("\n");
}

int displayServerHelpScreen() 
{
  Serial.println("Type a command (case insensitive), then press [Enter].");
  intCommandSucceeded = true;
  return intCommandSucceeded;
}

int displayAllHelpScreens() 
{
  displayServerHelpScreen(); 
  displayAppHelpScreen(); 
  intCommandSucceeded = true;
  return intCommandSucceeded;
}

String getCommand()
{
  int intReadByte = 0;
  String strReadData = "";

  //As long as the byte just read is not a line-feed or CR...
  while ((intReadByte != 10) && (intReadByte != 13))
  {
    //...and the serial port buffer has data, read a byte from it.
    if (Serial.available()) 
    {
      intReadByte = Serial.read(); 

      //If the byte just read is not a line-feed or CR...
      if ((intReadByte != 10) && (intReadByte != 13))
      {
        //...then add it to the string.
        strReadData.concat(char(intReadByte)); 
      }
    }
  }

  //Return the string
  return strReadData;
}

int runCommand(String strCommand)
{
  intCommandSucceeded = 0;

  Serial.print("Executing command: ");
  Serial.println(strCommand);

  if (strCommand.equals("help")) {
    intCommandSucceeded = displayAllHelpScreens();
  }
  else if (strCommand.startsWith("sendnec")) {
    intCommandSucceeded = sendnec(strCommand);
  }
  else if (strCommand.startsWith("sendsirc")) {
    intCommandSucceeded = sendsirc(strCommand);
  }
  else if (strCommand.startsWith("sendrc5")) {
    intCommandSucceeded = sendrc5(strCommand);
  }
  else if (strCommand.startsWith("sendrc6")) {
    intCommandSucceeded = sendrc6(strCommand);
  }
  else if (strCommand.startsWith("senddish")) {
    intCommandSucceeded = senddish(strCommand);
  }
  else if (strCommand.startsWith("sendsharp")) {
    intCommandSucceeded = sendsharp(strCommand);
  }
  else if (strCommand.startsWith("sendpanasonic")) {
    intCommandSucceeded = sendpanasonic(strCommand);
  }
  else if (strCommand.startsWith("sendjvc")) {
    intCommandSucceeded = sendjvc(strCommand);
  }
  else if (strCommand.startsWith("sendsanyo")) {
    intCommandSucceeded = sendsanyo(strCommand);
  }
  else if (strCommand.startsWith("sendmitsubishi")) {
    intCommandSucceeded = sendmitsubishi(strCommand);
  }
  else {
    intCommandSucceeded = false;
  }

  //Return the success or failure of this command.
  return intCommandSucceeded;
}
