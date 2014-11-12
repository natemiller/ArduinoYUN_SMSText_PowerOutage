ArduinoYUN_SMSText_PowerOutage
==============================
    
2014 Nate Miller
Send An SMS text message when power to a particular outlet is lost. 

This is a rather odd sketch, but was constructed around an issue where we had two power sources in our building (one standard and one based off a backup generator). We needed a means of identifying when one of these sources went off because important equipment (which could not be switched to the other power source) was on that line. Some type of voltage detector would be great but I didn't have one of those, so in a pinch I decided instead to use the loss of power to a device (in this case a nightlight) as a signal. 

This code utilizes an Arduino YUN and assumes that the YUN is powered by the consistent power source and the nightlight is plugged into the less reliable power source. When the power to the nightlight fails, the light goes out and this change of state is detected by a photodiode and the Arduino YUN sends an SMS text relating the power outage (this also assumes that the wireless router still has power doing this outage). When the power returns, the light comes on, this change in state is detected, resulting in a second SMS message being sent. 

Who knows how broadly applicable this is, but it was quick to write and did the job using relatively simple equipment laying around the lab.
    
The user will need both a Twilio and a Temboo account (both free).
