#ifndef __SHCUSTOMPROTOCOL_H__
#define __SHCUSTOMPROTOCOL_H__
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
// selezione la configurazione nella cartella lgfx_user
// #include <LGFX_AUTODETECT.hpp>  // Preparare la classe "LGFX"
// #include <lgfx_user/LGFX_ESP8266_sample.hpp>
#include <lgfx_user/LGFX_ESP32_esp32-2432s028.hpp> 

#include <Arduino.h>
#include <map>
#include <BleGamepad.h> // libreria bluetooh

static LGFX tft;


static const int SCREEN_WIDTH = 320;
static const int SCREEN_HEIGHT = 240;
static const int X_CENTER = SCREEN_WIDTH / 2;
static const int Y_CENTER = SCREEN_HEIGHT / 2;
static const int ROWS = 5;
static const int COLS = 5;
static const int CELL_WIDTH = SCREEN_WIDTH / COLS;
static const int HALF_CELL_WIDTH = CELL_WIDTH / 2;
static const int CELL_HIGHT = SCREEN_HEIGHT / ROWS;
static const int HALF_CELL_HIGHT = CELL_HIGHT / 2;
static const int COL[] = {0, CELL_WIDTH, CELL_WIDTH * 2, CELL_WIDTH * 3, CELL_WIDTH * 4, CELL_WIDTH * 6, CELL_WIDTH * 7};
static const int ROW[] = {0, CELL_HIGHT, CELL_HIGHT * 2, CELL_HIGHT * 3, CELL_HIGHT * 4, CELL_HIGHT * 6, CELL_HIGHT * 7};


std::map<String, String> prevData;
std::map<String, int32_t> prevColor;

// configuro ble per gamepad

BleGamepad bleGamepad("ESP32 Touch Gamepad", "YourCompany", 100);
BleGamepadConfiguration bleGamepadConfig;

// configuro ble per gamepad


class SHCustomProtocol
{
private:
	// Global variables
	int rpmPercent = 50;
	int prev_rpmPercent = 50;
	int rpmRedLineSetting = 90;
	String gear = "N";
	String prev_gear;
	String speed = "0";
	String currentLapTime = "00:00.00";
	String lastLapTime = "00:00.00";
	String bestLapTime = "00:00.00";
	String sessionBestLiveDeltaSeconds = "0.000";
	String sessionBestLiveDeltaProgressSeconds = "0.00";
	String tyrePressureFrontLeft = "00.0";
	String tyrePressureFrontRight = "00.0";
	String tyrePressureRearLeft = "00.0";
	String tyrePressureRearRight = "00.0";
	String tcLevel = "0";
	String tcActive = "0";
	String absLevel = "0";
	String absActive = "0";
	String isTCCutNull = "True";
	String tcTcCut = "0  0";
	String brakeBias = "0";
	String brake = "0";
	String lapInvalidated = "False";
    uint16_t touchX, touchY;	// definisce i due interi per gestione touchscreen
	

public:
	/*
	CUSTOM PROTOCOL CLASS
	SEE https://github.com/zegreatclan/SimHub/wiki/Custom-Arduino-hardware-support

	GENERAL RULES :
		- ALWAYS BACKUP THIS FILE, reinstalling/updating SimHub would overwrite it with the default version.
		- Read data AS FAST AS POSSIBLE in the read function
		- NEVER block the arduino (using delay for instance)
		- Make sure the data read in "read()" function READS ALL THE DATA from the serial port matching the custom protocol definition
		- Idle function is called hundreds of times per second, never use it for slow code, arduino performances would fall
		- If you use library suspending interrupts make sure to use it only in the "read" function when ALL data has been read from the serial port.
			It is the only interrupt safe place

	COMMON FUNCTIONS :
		- FlowSerialReadStringUntil('\n')
			Read the incoming data up to the end (\n) won't be included
		- FlowSerialReadStringUntil(';')
			Read the incoming data up to the separator (;) separator won't be included
		- FlowSerialDebugPrintLn(string)
			Send a debug message to simhub which will display in the log panel and log file (only use it when debugging, it would slow down arduino in run conditions)

	*/

	// Called when starting the arduino (setup method in main sketch)
	void setup()
	{
	//    Serial.begin(115200);   //x debug
    //    Serial.println("Test seriale avviato!"); //x debug
		
		
		tft.init();
		tft.setRotation(1);
		tft.fillScreen(TFT_BLACK);


//Questa parte di 10 righe , dopo il commento ,del codice configura il comportamento del tuo gamepad Bluetooth emulato tramite l'ESP32. Ecco una spiegazione dettagliata di ogni riga:

//Dettagli delle Funzioni
//bleGamepadConfig.setAutoReport(false);
//Questa funzione disabilita la segnalazione automatica dello stato del gamepad.
//Significa che lo stato del gamepad non verrà inviato automaticamente ai dispositivi collegati. Dovrai chiamare manualmente bleGamepad.sendReport() per inviare lo stato del gamepad quando necessario.
//bleGamepadConfig.setAxesMax(32760);

//Questa funzione imposta il valore massimo per gli assi (X, Y, Z, ecc.) del gamepad.
//Anche se non stai usando gli assi nel tuo progetto, è buona pratica impostare un valore massimo sensato.
//bleGamepadConfig.setIncludeSlider1(false);

//Questa funzione specifica che il gamepad non includerà un asse slider1.
//Poiché stai utilizzando solo pulsanti touch, non hai bisogno di assi slider.
//bleGamepadConfig.setIncludeXAxis(false);

//Questa funzione specifica che il gamepad non includerà l'asse X.
//Non stai usando assi nel tuo progetto, quindi li escludi tutti.
//bleGamepadConfig.setIncludeYAxis(false);

//Questa funzione specifica che il gamepad non includerà l'asse Y.
//bleGamepadConfig.setIncludeZAxis(false);

//Questa funzione specifica che il gamepad non includerà l'asse Z.
//bleGamepadConfig.setIncludeRxAxis(false);

//Questa funzione specifica che il gamepad non includerà l'asse Rx (asse di rotazione X).
//bleGamepadConfig.setIncludeRyAxis(false);

//Questa funzione specifica che il gamepad non includerà l'asse Ry (asse di rotazione Y).
//bleGamepadConfig.setIncludeRzAxis(false);

//Questa funzione specifica che il gamepad non includerà l'asse Rz (asse di rotazione Z).
//bleGamepadConfig.setButtonCount(6);

//Questa funzione imposta il numero di pulsanti sul gamepad a 6.
//Questo corrisponde ai 6 pulsanti touch che vuoi configurare sul tuo display.
//bleGamepad.begin(&bleGamepadConfig);

//Questa funzione inizializza il gamepad Bluetooth con la configurazione specificata.
//Dopo questa chiamata, il gamepad è pronto per essere utilizzato e inviato ai dispositivi collegati.

        bleGamepadConfig.setAutoReport(true);  // in false non invia i comandi a windows
        bleGamepadConfig.setAxesMax(32760);
        bleGamepadConfig.setIncludeSlider1(false);
        bleGamepadConfig.setIncludeXAxis(false);
        bleGamepadConfig.setIncludeYAxis(false);
        bleGamepadConfig.setIncludeZAxis(false);
        bleGamepadConfig.setIncludeRxAxis(false);
        bleGamepadConfig.setIncludeRyAxis(false);
        bleGamepadConfig.setIncludeRzAxis(false);
        bleGamepadConfig.setButtonCount(6);  // 6 touch buttons
        bleGamepad.begin(&bleGamepadConfig);
    // Serial.println("Configurazione BleGamepad completata.");   //x debug



	}




	// Called when new data is coming from computer
	void read()
	{
		String full = "";

		speed = FlowSerialReadStringUntil(';').toInt();
		gear = FlowSerialReadStringUntil(';');
		rpmPercent = FlowSerialReadStringUntil(';').toInt();
		rpmRedLineSetting = FlowSerialReadStringUntil(';').toInt();
		currentLapTime = FlowSerialReadStringUntil(';');
		lastLapTime = FlowSerialReadStringUntil(';');
		bestLapTime = FlowSerialReadStringUntil(';');
		sessionBestLiveDeltaSeconds = FlowSerialReadStringUntil(';');
		sessionBestLiveDeltaProgressSeconds = FlowSerialReadStringUntil(';');
		tyrePressureFrontLeft  = FlowSerialReadStringUntil(';');
		tyrePressureFrontRight  = FlowSerialReadStringUntil(';');
		tyrePressureRearLeft  = FlowSerialReadStringUntil(';');
		tyrePressureRearRight  = FlowSerialReadStringUntil(';');
		tcLevel  = FlowSerialReadStringUntil(';');
		tcActive  = FlowSerialReadStringUntil(';');
		absLevel  = FlowSerialReadStringUntil(';');
		absActive  = FlowSerialReadStringUntil(';');
		isTCCutNull  = FlowSerialReadStringUntil(';');
		tcTcCut  = FlowSerialReadStringUntil(';');
		brakeBias  = FlowSerialReadStringUntil(';');
		brake  = FlowSerialReadStringUntil(';');
		lapInvalidated  = FlowSerialReadStringUntil(';');

		const String rest = FlowSerialReadStringUntil('\n');
	}

	// Called once per arduino loop, timing can't be predicted,
	// but it's called between each command sent to the arduino
	void loop()
	{
        readTouch(); // Leggi il touchscreen dello schermo
		
		drawRpmMeter(0, 0, SCREEN_WIDTH, HALF_CELL_HIGHT);
		drawGear(COL[2], COL[1]);
				
		// First+Second Column (Lap times)
		drawCell(COL[0], ROW[1], bestLapTime, "bestLapTime", "Best Lap", "left");
		drawCell(COL[0], ROW[2], lastLapTime, "lastLapTime", "Last Lap", "left");
		drawCell(COL[0], ROW[3], currentLapTime, "currenLapTime", "Current Lap", "left", lapInvalidated == "True" ? TFT_RED : TFT_WHITE);


		// Third Column (speed)
		drawCell(COL[2], ROW[3], speed, "speed", "Speed");

		// Fourth+Fifth Column (delta)
		drawCell(SCREEN_WIDTH, ROW[1], sessionBestLiveDeltaSeconds, "sessionBestLiveDeltaSeconds", "Delta", "right", sessionBestLiveDeltaSeconds.indexOf('-') >= 0 ? TFT_GREEN : TFT_RED);
		drawCell(SCREEN_WIDTH, ROW[2], sessionBestLiveDeltaProgressSeconds, "sessionBestLiveDeltaProgressSeconds", "Delta P", "right", sessionBestLiveDeltaProgressSeconds.indexOf('-') >= 0 ? TFT_GREEN : TFT_RED);
		

		// (TC, ABS, BB)
		if (isTCCutNull == "False")
			drawCell(COL[0], ROW[4], tcTcCut, "tcTcCut", "TC TC2", "center", TFT_YELLOW);
		else
			drawCell(COL[0], ROW[4], tcLevel, "tcLevel", "TC", "center", TFT_YELLOW);
		drawCell(COL[1], ROW[4], absLevel, "absLevel", "ABS", "center", TFT_BLUE);
		drawCell(COL[2], ROW[4], brakeBias, "brakeBias", "BB", "center", TFT_MAGENTA);

		// (tyre pressure)
		drawCell(COL[3], ROW[3], tyrePressureFrontLeft, "tyrePressureFrontLeft", "FL", "center", TFT_CYAN);
		drawCell(COL[4], ROW[3], tyrePressureFrontRight, "tyrePressureFrontRight", "FR", "center", TFT_CYAN);
		drawCell(COL[3], ROW[4], tyrePressureRearLeft, "tyrePressureRearLeft", "RL", "center", TFT_CYAN);
		drawCell(COL[4], ROW[4], tyrePressureRearRight, "tyrePressureRearRight", "RR", "center", TFT_CYAN);
	}

	// Called once between each byte read on arduino,
	// THIS IS A CRITICAL PATH :
	// AVOID ANY TIME CONSUMING ROUTINES !!!
	// PREFER READ OR LOOP METHOS AS MUCH AS POSSIBLE
	// AVOID ANY INTERRUPTS DISABLE (serial data would be lost!!!)
	void idle()
	{
	}

	void drawGear(int32_t x, int32_t y)
	{
		// draw gear only when it changes
		if (gear != prev_gear)
		{
			// tft.loadFont("Formula1_Regular_web_072pt7b", SPIFFS);
			tft.setTextColor(TFT_YELLOW, TFT_BLACK);
			tft.setTextSize(8);
			tft.setTextDatum(MC_DATUM);
			tft.setCursor(x + 12, y + HALF_CELL_HIGHT);
			tft.print(gear);
			tft.setTextSize(1);
			tft.setTextDatum(TL_DATUM);

			prev_gear = gear;
		}
	}

	boolean isDrawGearRpmRedRec()
	{
		if (rpmPercent >= rpmRedLineSetting)
		{
			return true;
		}
		return false;
	}

	void drawRpmMeter(int32_t x, int32_t y, int width, int height)
	{
		int meterWidth = (width * rpmPercent) / 100;

		int yPlusOne = y + 1;
		int innerWidth = width - meterWidth - 1;
		int innerHeight = height - 4;

		if (prev_rpmPercent > rpmPercent)
		{
			tft.fillRect(meterWidth, yPlusOne, innerWidth, innerHeight, TFT_BLACK); // clear the part after the current rect width
		}

		if (rpmPercent >= rpmRedLineSetting)
		{
			tft.fillRect(x, yPlusOne, meterWidth - 2, innerHeight, TFT_RED);
		}
		else if (rpmPercent >= rpmRedLineSetting - 5)
		{
			tft.fillRect(x, yPlusOne, meterWidth - 2, innerHeight, TFT_ORANGE);
		}
		else
		{
			tft.fillRect(x, yPlusOne, meterWidth - 2, innerHeight, TFT_GREEN);
		}

		// draw the frame only if it ont there
		if (prev_rpmPercent == 50) tft.drawRect(x, y, width, height-2, TFT_WHITE);
		
		prev_rpmPercent = rpmPercent;
	}

// La funzione drawCell disegna una cella sullo schermo e aggiorna il suo contenuto solo se i dati o il colore sono cambiati. 

	void drawCell(int32_t x, int32_t y, String data, String id, String name = "Data", String align = "center", int32_t color = TFT_WHITE, int fontSize = 4)
	{
		const static int titleHeight = 19;
		const static int hPadding = 5;
		const static int vPadding = 1;

		tft.setTextColor(color, TFT_BLACK);

		const bool dataChanged =  (prevData[id] != data);
		const bool colorChanged =  (prevColor[id] != color);

		if (dataChanged) {

			if (align == "left")
			{
				
				if (colorChanged) tft.drawRoundRect(x, y, CELL_WIDTH * 2 - 1, CELL_HIGHT - 2, 5, color);		// Rectangle
				if (colorChanged) tft.drawString(name, x + hPadding, y + vPadding, 2);						// Title
				tft.drawString(data, x + hPadding, y + titleHeight, fontSize); // Data
			}
			else if (align == "right")
			{
				if (colorChanged) tft.drawRoundRect(x - (CELL_WIDTH * 2), y, CELL_WIDTH * 2 - 1, CELL_HIGHT - 2, 5, color); // Rectangle
				if (colorChanged) tft.drawRightString(name, x - hPadding, y + vPadding, 2);						// Title
				tft.drawRightString(data, x - hPadding, y + titleHeight, fontSize);	  // Data
			}
			else // "center"
			{
				if (colorChanged) tft.drawRoundRect(x, y, CELL_WIDTH - 2, CELL_HIGHT - 2, 5, color);	 // Rectangle
				if (colorChanged) tft.drawCentreString(name, x + HALF_CELL_WIDTH, y + vPadding, 2);			 // Title
				tft.drawCentreString(data, x + HALF_CELL_WIDTH, y + titleHeight, fontSize); // Data
			}

			// Clean the previous speed if it was wider
			if (prevData[id].length() > data.length())
			{
				tft.setTextColor(TFT_BLACK, TFT_BLACK);
				if (align == "left")
				{
					tft.drawString(prevData[id], x + hPadding, y + titleHeight, fontSize);
				}
				else if (align == "right")
				{
					tft.drawRightString(prevData[id], x - hPadding, y + titleHeight, fontSize);
				}
				else
				{
					tft.drawCentreString(prevData[id], x + HALF_CELL_WIDTH, y + titleHeight, fontSize);
				}
			}

			prevData[id] = data;
			prevColor[id] = color;
		}

	}

    void readTouch()
    {
        if (tft.getTouch(&touchX, &touchY))
		        

        {
        //    tft.fillCircle(touchX, touchY, 5, TFT_RED); // Visualizza le coordinate del tocco PER DEBUG	
		//	  Serial.print("Tocco rilevato alle coordinate: "); //x debug
        //    Serial.print(touchX); //x debug
        //    Serial.print(", "); //x debug
        //    Serial.println(touchY); //x debug


// Questa sezione del codice gestisce il rilevamento del tocco sullo schermo e mappa le coordinate del tocco a un pulsante 
// virtuale, inviando quindi un comando tramite Bluetooth utilizzando il BleGamepad. Ecco una spiegazione dettagliata di ciò 
// che fa ogni parte del codice:

	        int buttonIndex = getTouchButtonIndex(touchX, touchY);

        //     Serial.print("Indice pulsante: ");  //x debug
        //     Serial.println(buttonIndex);       //x debug

            if (buttonIndex != -1)
            {
                bleGamepad.press(buttonIndex + 1);

		//		Serial.print("Pulsante ");          //x debug
        // 		Serial.print(buttonIndex + 1);       //x debug
        //      Serial.println("premuto");   //x debug

                delay(100); // debounce delay
                bleGamepad.release(buttonIndex + 1);
	    //      Serial.print("Pulsante ");          //x debug
        //      Serial.print(buttonIndex + 1);     //x debug
        //      Serial.println(" rilasciato.");   //x debug
            }		
        }
    }


// La funzione getTouchButtonIndex calcola l'indice di un pulsante touch in base alle coordinate di tocco x e y sullo schermo. 
// In pratica, divide lo schermo in una griglia di pulsanti, quindi determina quale pulsante è stato toccato.

    int getTouchButtonIndex(int x, int y)
    {
        int buttonWidth = SCREEN_WIDTH / 3;
        int buttonHeight = SCREEN_HEIGHT / 2;
        int col = x / buttonWidth;
        int row = y / buttonHeight;
        return col + row * 3; // Restituisce l'indice del pulsante (0 a 5)
    }

};

#endif