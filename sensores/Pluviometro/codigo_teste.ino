#define REED 13    // pin onde o sensor magnetico esta conectado

#define DIAMETRO 125       // diametro interno do balde
#define RAIO 6.25      // raio interno do balde
#define VOLUME 3.05      // volume da bascula (em cm3) (1cm3 == 1ml) (1ml == 1000mm3)

// Variáveis pluviometro:
int val = 0;
int old_val = 0;
float volume_coletado;
volatile unsigned long ContactBounce = 0;
volatile unsigned long REEDCOUNT = 0;

// This is the function that the interrupt calls to increment the turning count
void IRAM_ATTR isr_rain () {
  if ((millis() - ContactBounce) > 50 ) { // debounce the switch contact.
    REEDCOUNT = REEDCOUNT + 1;              // Adiciona 1 à cntagem de pulsos
    ContactBounce = millis();
    // Serial.println("funcao interrupcao chuva");
  }
}

void get_rain(){
    // float area_recipiente = 3.14159265 * (RAIO * RAIO); // área da seção transversal do recipiente em cm²
    // float volume_por_virada = (VOLUME/area_recipiente);
    volume_coletado = (REEDCOUNT * 0.25) * 10; // volume total coletado em cm³

    Serial.print("Viradas: ");
    Serial.println(REEDCOUNT);

    Serial.print("Chuva: ");
    Serial.print (volume_coletado);
    Serial.println(" mm");
}

void setup() {
  Serial.begin(115200);       // velocidade monitor serial

  pinMode(REED, INPUT_PULLUP);
  attachInterrupt(REED, isr_rain, FALLING);
}

void loop() {
  get_rain();
  delay(1000);
}
