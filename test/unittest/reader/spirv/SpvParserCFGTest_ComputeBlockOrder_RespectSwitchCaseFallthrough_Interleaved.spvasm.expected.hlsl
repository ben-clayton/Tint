static uint var_1 = 0u;

void main_1() {
  switch(42u) {
    case 30u: {
      /* fallthrough */
    }
    case 50u: {
      break;
    }
    case 20u: {
      /* fallthrough */
    }
    case 40u: {
      break;
    }
    default: {
      break;
    }
  }
  return;
}

void main() {
  main_1();
  return;
}