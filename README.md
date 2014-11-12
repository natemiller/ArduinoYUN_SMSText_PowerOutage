ArduinoYUN_SMSText_PowerOutage
==============================

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
    
      The user will need both a Twilio and a Temboo account (both free).
