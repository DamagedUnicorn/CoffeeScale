void LCDPrint(uint8_t scale, float value)
{
  lcd.setCursor(0, scale);
  lcd.print("                ");

  switch (scale)
  {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("B:");
      break;

    case 1:
      lcd.setCursor(0, 1);
      lcd.print("L:");
      break;

    default:
      break;
  }

  if (value >= 0)
  {
    lcd.setCursor(4, scale);
  }
  else
  {
    lcd.setCursor(3, scale);
  }
  lcd.print(String(value, 1));
}

void LCDPrintTare(uint8_t num)
{
  //lcd.setCursor(3, num);
  //lcd.print("              ");
  lcd.setCursor(3, num);
  lcd.print("TARING");
}
