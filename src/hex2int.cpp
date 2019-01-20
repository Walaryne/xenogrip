int hex2int(char buf[2]) {
    int val;
    switch(buf[0]) {
    case '0':
        val = 0;
        break;
    case '1':
        val = 16;
        break;
    case '2':
        val = 16*2;
        break;
    case '3':
        val = 16*3;
        break;
    case '4':
        val = 16*4;
        break;
    case '5':
        val = 16*5;
        break;
    case '6':
        val = 16*6;
        break;
    case '7':
        val = 16*7;
        break;
    case '8':
        val = 16*8;
        break;
    case '9':
        val = 16*9;
        break;
    case 'a':
        val = 16*10;
        break;
    case 'b':
        val = 16*11;
        break;
    case 'c':
        val = 16*12;
        break;
    case 'd':
        val = 16*13;
        break;
    case 'e':
        val = 16*14;
        break;
    case 'f':
        val = 16*15;
    }
    switch(buf[1]) {
    case '0':
        val += 0;
        break;
    case '1':
        val += 1;
        break;
    case '2':
        val += 2;
        break;
    case '3':
        val += 3;
        break;
    case '4':
        val += 4;
        break;
    case '5':
        val += 5;
        break;
    case '6':
        val += 6;
        break;
    case '7':
        val += 7;
        break;
    case '8':
        val += 8;
        break;
    case '9':
        val += 9;
        break;
    case 'a':
        val += 10;
        break;
    case 'b':
        val += 11;
        break;
    case 'c':
        val += 12;
        break;
    case 'd':
        val += 13;
        break;
    case 'e':
        val += 14;
        break;
    case 'f':
        val += 15;
    }
    return val;
}
