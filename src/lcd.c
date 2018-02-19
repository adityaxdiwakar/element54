#include "main.h"


void lcdCounter(void *parameter)
{
    while (true)
    {
        lcdSetText(uart1, 1, "   1961 Xenon   ");
        lcdPrint(uart1, 2, "L: %d 4B: %d", analogRead(ARM_SENSOR), analogRead(BAR_SENSOR));
        delay(100);
    }
}

void lcdAuton_Diagnositics(int selectVal)
{
    // add page information
}

void lcdAuton_Pages(int selectVal)
{
    if (selectVal == 0)
    {
        lcdSetText(uart1, 1, " Swipe right >> ");
        lcdSetText(uart1, 2, "[None]    [PICK]");
    }
    if (selectVal == 1)
    {
        lcdSetText(uart1, 1, "   20 Pt Mogo   ");
        lcdSetText(uart1, 2, "    [Select]    ");
    }
    if (selectVal == 2)
    {
        lcdSetText(uart1, 1, "   5 Pt Mogo    ");
        lcdSetText(uart1, 2, "    [Select]    ");
    }
    if (selectVal == 3)
    {
        lcdSetText(uart1, 1, "   Stationary   ");
        lcdSetText(uart1, 2, "    [Select]    ");
    }
    if (selectVal == 4)
    {
        lcdSetText(uart1, 1, "   Prog Skill   ");
        lcdSetText(uart1, 2, "    [Select]    ");
    }
}

void lcdAuton_Init()
{
    lcdSetText(uart1, 1, "Initializing....");
    lcdSetText(uart1, 2, "[              ]");
    wait(100);
    lcdSetText(uart1, 2, "[=             ]");
    wait(100);
    lcdSetText(uart1, 2, "[==            ]");
    wait(100);
    lcdSetText(uart1, 2, "[===           ]");
    wait(100);
    lcdSetText(uart1, 2, "[====          ]");
    wait(100);
    lcdSetText(uart1, 2, "[=====         ]");
    wait(100);
    lcdSetText(uart1, 2, "[======        ]");
    wait(100);
    lcdSetText(uart1, 2, "[=======       ]");
    wait(100);
    lcdSetText(uart1, 2, "[========      ]");
    wait(100);
    lcdSetText(uart1, 2, "[=========     ]");
    wait(100);
    lcdSetText(uart1, 2, "[==========    ]");
    wait(100);
    lcdSetText(uart1, 2, "[==========    ]");
    wait(100);
    lcdSetText(uart1, 2, "[===========   ]");
    wait(100);
    lcdSetText(uart1, 2, "[============  ]");
    wait(100);
    lcdSetText(uart1, 2, "[============= ]");
    wait(100);
    lcdSetText(uart1, 2, "[==============]");
    wait(250);
}

void lcdAuton()
{
    lcdSetBacklight(uart1, 1);
    lcdAuton_Init();
    lcdSetText(uart1, 1, "  Select Auton  ");
    lcdSetText(uart1, 2, "[Done]      [>>]");
    int lcdAutonPage = 0;
    bool breaker = 1;
    while (breaker)
    {
        lcdAuton_Pages(lcdAutonPage);
        if (lcdReadButtons(uart1) == 4)
            lcdAutonPage += 1;
        if (lcdAutonPage > 0)
        {
            if (lcdReadButtons(uart1) == 1)
                lcdAutonPage -= 1;
        }
        if (lcdReadButtons(uart1) == 2)
        {
            breaker = 0;
        }
        if (lcdReadButtons(uart1) > 0)
        {
            delay(500);
        }
        delay(10);
    }
    lcdSetText(uart1, 1, "Selected.");
    selectAuton[0] = lcdAutonPage;
    if (selectAuton[0] == 1 || selectAuton[0] == 2 || selectAuton[0] == 3)
    {
        if (selectAuton[0] == 1 || selectAuton[0] == 2)
        {
            lcdSetText(uart1, 1, " Cone quantity? ");
            lcdSetText(uart1, 2, "[1]          [2]");
            while (true)
            {
                if (lcdReadButtons(uart1) == 1)
                {
                    lcdAutonPage = 1;
                    break;
                }
                else if (lcdReadButtons(uart1) == 4)
                {
                    lcdAutonPage = 2;
                    break;
                }
                delay(10);
            }
            selectAuton[1] = lcdAutonPage;
            lcdSetText(uart1, 1, "   What side?   ");
            lcdSetText(uart1, 2, "[R]          [B]");
            wait(250);
            while (true)
            {
                if (lcdReadButtons(uart1) == 1)
                {
                    lcdAutonPage = 1;
                    break;
                }
                else if (lcdReadButtons(uart1) == 4)
                {
                    lcdAutonPage = 2;
                    break;
                }
                delay(10);
            }
            selectAuton[2] = lcdAutonPage;
        }
        if (selectAuton[0] == 3)
        {
            lcdSetText(uart1, 1, "      GTFO      ");
            lcdSetText(uart1, 2, "[L]   [NO]   [R]");
            while (true)
            {
                if (lcdReadButtons(uart1) == 1)
                {
                    lcdAutonPage = 1;
                    break;
                }
                if (lcdReadButtons(uart1) == 2)
                {
                    lcdAutonPage = 2;
                    break;
                }
                if (lcdReadButtons(uart1) == 4)
                {
                    lcdAutonPage = 3;
                    break;
                }
                delay(10);
            }
            selectAuton[1] = lcdAutonPage;
            selectAuton[2] = 0;
        }
    }
    lcdSetText(uart1, 1, "");
    lcdSetText(uart1, 2, "");
    lcdSetBacklight(uart1, 0);
}

void lcdMain(void *parameter)
{

}