double euler6(double limit) {
  double sum = 0;
  double squares = 0;
  double i = limit;
  do {
    sum += i;
    squares += i * i;
    --i;
  } while (i > 0);

  return sum * sum - squares;
}
