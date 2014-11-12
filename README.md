ArduinoYUN_SMSText_PowerOutage
==============================
    
    2014 Nate Miller
    
    Send An SMS text message when power to a particular outlet is lost. 
    This is a rather odd sketch, but was constructed around an issue where we
    had two power sources in our building (one standard and one based off a backup generator). 
    We needed a means of identifying when one of these sources went off because important equipment 
    (which could not be switched to the other power source) was on that line. Some type of voltage 
    detector would be great but I didn't have one of those, so in a pinch I decided instead to use 
    the loss of power to a device (in this case a nightlight) as a signal. 
    
    This code utilizes an Arduino YUN and assumes that the YUN is powered by the consistent power source and 
    the nightlight was plugged into the less reliable power source. When the power to the nightlight failed, 
    the light would go out and this change would be detected by a photodiode and the Arduino YUN would 
    send an SMS text relating the power outage (this also assumes that the wireless router still has power 
    doing this outage). When the power returns, the light come on, and this change in state will be detected, 
    resulting in a second SMS message being sent. 
    
    Who knows how broadly applicable this is, but it was very quick to write and did the job using simple
    electrical parts laying around the lab.
    
    The user will need both a Twilio and a Temboo account (both free).
