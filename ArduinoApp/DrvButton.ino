bool isButtonPressed(int num)
{
  switch (num)
  {
    case 0:
      return digitalRead(tareButton0Pin);
      break;

    case 1:
      return digitalRead(tareButton1Pin);
      break;

    default:
      return false;
      break;
  }
}
