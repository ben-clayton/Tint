static uint var_1 = 0u;

void main_1() {
  switch(42u) {
    case 20u: {
      if (false) {
      }
      if (false) {
        break;
      }
      /* fallthrough */
    }
    default: {
      /* fallthrough */
    }
    case 50u: {
      if (false) {
      }
      break;
    }
  }
  return;
}

void main() {
  main_1();
  return;
}