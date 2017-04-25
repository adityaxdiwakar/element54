signed char cap (int pwr)
{
    if (pwr > 127) return 127;
    else if (pwr < -127) return -127;
    else return pwr;
};
