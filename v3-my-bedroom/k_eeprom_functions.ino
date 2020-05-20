void writeStringToEEPROM(int addr, String myStr){
  EEPROM.update(addr, myStr.length());
  
  for(int i=0 ; i < myStr.length() ; i++)
  {
    EEPROM.update(addr + i + 1, myStr[i]);
  }
}

String readStringFromEEPROM(int addr){
  String myStr;

  int strLength = EEPROM.read(addr);
  
  for(byte b=0; b < strLength; b++)
  {
     if (EEPROM.read(addr + b + 1) > 14){
       myStr += char(EEPROM.read(addr + b + 1));
     }
  }

  return myStr;
}
