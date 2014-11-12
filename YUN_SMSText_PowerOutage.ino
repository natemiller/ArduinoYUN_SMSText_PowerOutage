 /*
    2014 Nate Miller
    Send An SMS text message when power to a particular outlet is lost. 
    
    This is a rather odd sketch, but was constructed around an issue we were
    in which there were two power sources in our building (one standard and one
    based off a backup generator). We needed a means of identifying when one of 
    these sources went off because important equipment (which could not be switched
    to the other power source) was on that line. This code currently assumes
    that the Arduino YUN is powered by the consistent power source and the light (in this
    case a nightlight) was plugged into the less reliable power source. When the power
    went out the nightlight would go out, this would be detected by the photosensor (diode)
    and the Arduino YUN would send an SMS text related the power outtage (this also assumes
    that the wireless router still has power doing this outtage). When the power comes back
    on, a second message is sent relating that information. Who knows how broadly applicable
    this is, but it was very quick to write and did the job. 
    
      The user will need both a Twilio and a Temboo account (both free). The passwords
      etc. associated with these accounts are typically kept on a second tab (TembooAccount.h)
      in the Arduino IDE and referenced by the code below.
  */
  
  #include <Bridge.h>
  #include <Temboo.h>
  #include "TembooAccount.h" // contains Temboo account information
  
  
  int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
  int photocellReading;     // the analog reading from the sensor divider
  int smsState = 0;        //initial SMS state
  
  unsigned long previousMillis_print = 0;  //intial timer value
  const long printInterval = 1000; //wait 1 sec between serial print
  unsigned long previousMillis_SMS = 0;    //intial timer value
  const long smsInterval = 1800000; //wait 30 min between sending SMS
  
  
  void setup() {
    
    Serial.begin(9600);
    Bridge.begin();            //start the bridge library for the YUN
  }
  
  void loop()
  {
    //create two timers, one for the SMS and one for printing and troubleshooting
    unsigned long timer_sms = millis();
    unsigned long timer_print = millis();
    
    photocellReading = analogRead(photocellPin);               //read the state of the photocell
    
    if(timer_print - previousMillis_print > printInterval) {    //timer code for troubleshooting the photocell and SMS state
     previousMillis_print = timer_print;
  Serial.print(smsState);
  Serial.print("  ");
  Serial.println(photocellReading);
    
    }
    
     if(timer_sms - previousMillis_SMS > smsInterval) {        //second timer to limit how often an SMS message can be send (smsInterval)
       previousMillis_SMS = timer_sms;
       
  
       
    if(photocellReading < 800) {                               //check if the light is OFF
           smsState = 1;                                       //if so...set the SMSstate to 1
           SendSMS();                                          //...and run the SendSMS function
         }
    if(photocellReading >= 800 & smsState == 1) {              //if the light is ON and the SMSstate is 1 (the light had been OFF)
           smsState = 0;                                       //reset the SMSstate to 0
           SendSMS();                                          //and run the SendSMS function
            
       }
    if(photocellReading >= 800 & smsState == 0){               //if the light is ON, and it had been ON previously
     }                                                         //do nothing...
   }
  }
 
 //----------------------------------------- 
 // Function to send an SMS text
 //-----------------------------------------
    
    void SendSMS() {
      
    // only try to send the SMS if we haven't already sent it successfully
   
  
      Serial.println("Running SendAnSMS...");
      
      // we need a Process object to send a Choreo request to Temboo
      TembooChoreo SendSMSChoreo;
  
      // invoke the Temboo client
      // NOTE that the client must be reinvoked and repopulated with
      // appropriate arguments each time its run() method is called.
      SendSMSChoreo.begin();
      
      // set Temboo account credentials
      SendSMSChoreo.setAccountName(TEMBOO_ACCOUNT);
      SendSMSChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
      SendSMSChoreo.setAppKey(TEMBOO_APP_KEY);
  
      // identify the Temboo Library choreo to run (Twilio > SMSMessages > SendSMS)
      SendSMSChoreo.setChoreo("/Library/Twilio/SMSMessages/SendSMS");
  
      // set the required choreo inputs
      // see https://www.temboo.com/library/Library/Twilio/SMSMessages/SendSMS/ 
      // for complete details about the inputs for this Choreo
  
      // the first input is a your AccountSID
      SendSMSChoreo.addInput("AccountSID", TWILIO_ACCOUNT_SID);
      
      // next is your Auth Token
      SendSMSChoreo.addInput("AuthToken", TWILIO_AUTH_TOKEN);
   
      // next is your Twilio phone number
      SendSMSChoreo.addInput("From", TWILIO_NUMBER);
      
      // next, what number to send the SMS to
      SendSMSChoreo.addInput("To", RECIPIENT_NUMBER);
  
      // finally, the text of the message to send
      if(smsState == 1) {
      SendSMSChoreo.addInput("Body", "Uh oh! The power is OFF! ");
      } else if (smsState == 0) {
      // finally, the text of the message to send
      SendSMSChoreo.addInput("Body", "Yahoo! The power is back ON! ");
      }
      // tell the Process to run and wait for the results. The 
      // return code (returnCode) will tell us whether the Temboo client 
      // was able to send our request to the Temboo servers
      unsigned int returnCode = SendSMSChoreo.run();
  
      // a return code of zero (0) means everything worked
      if (returnCode == 0) {
          Serial.println("Success! SMS sent!");
    
      } else {
        // a non-zero return code means there was an error
        // read and print the error message
        while (SendSMSChoreo.available()) {
          char c = SendSMSChoreo.read();
          Serial.print(c);
        }
      } 
      SendSMSChoreo.close();
      Serial.println("Waiting...");
      Serial.println(smsState);
    
  }
