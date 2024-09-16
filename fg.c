#include <ctype.h>
#include <math.h>
#include <stdio.h>

float get_frequency(char note, int octave, int sharp);
int compute_register_value(double frequency);

int main() {
  char input[4]; // To store the input note, e.g., C#4
  char note;
  int octave, sharp = 0;
  float frequency;
  double register_value;
  int register_value_int;

  printf("Enter the note (e.g., C#4, Bb2, F3): ");
  scanf("%3s", input);

  note = toupper(input[0]);
  sharp = 0;

  if (input[1] == '#' || input[1] == 'b') {
    sharp = (input[1] == '#') ? 1 : -1;
    octave = input[2] - '0'; // Convert char to int
  } else {
    octave = input[1] - '0'; // Convert char to int
  }

  if (octave < 1 || octave > 5) {
    printf("Invalid octave. Please enter an octave between 1 and 5.\n");
    return 1;
  }

  frequency = get_frequency(note, octave, sharp);

  if (frequency > 0) {
    printf("\nNote: %s\n", input);
    printf("Frequency: %.2f Hz\n", frequency);

    if (frequency >= 64.0 && frequency <= 131000.0) {
      register_value = 2048.0 - (131072.0 / frequency);
      register_value_int = (int)round(register_value);

      printf("Register Value: %d (Decimal), 0x%X (Hexadecimal)\n",
             register_value_int, register_value_int);
    } else {
      printf("Frequency %.2f Hz is out of range for register value calculation "
             "(64 Hz - 131 kHz).\n",
             frequency);
    }
  } else {
    printf("Invalid note. Please enter a valid note between C1 and B5.\n");
  }

  return 0;
}

float get_frequency(char note, int octave, int sharp) {
  // Frequencies for notes in octave 1 to 5
  float frequencies[12][5] = {
      {32.70, 65.41, 130.81, 261.63, 523.25},  // C
      {34.65, 69.30, 138.59, 277.18, 554.37},  // C#
      {36.71, 73.42, 146.83, 293.66, 587.33},  // D
      {38.89, 77.78, 155.56, 311.13, 622.25},  // D#
      {41.20, 82.41, 164.81, 329.63, 659.25},  // E
      {43.65, 87.31, 174.61, 349.23, 698.46},  // F
      {46.25, 92.50, 185.00, 369.99, 739.99},  // F#
      {49.00, 98.00, 196.00, 392.00, 783.99},  // G
      {51.91, 103.83, 207.65, 415.30, 830.61}, // G#
      {55.00, 110.00, 220.00, 440.00, 880.00}, // A
      {58.27, 116.54, 233.08, 466.16, 932.33}, // A#
      {61.74, 123.47, 246.94, 493.88, 987.77}  // B
  };

  int note_index;

  switch (note) {
  case 'C':
    note_index = 0;
    break;
  case 'D':
    note_index = 2;
    break;
  case 'E':
    note_index = 4;
    break;
  case 'F':
    note_index = 5;
    break;
  case 'G':
    note_index = 7;
    break;
  case 'A':
    note_index = 9;
    break;
  case 'B':
    note_index = 11;
    break;
  default:
    return -1.0; // Invalid note
  }

  note_index += sharp;

  if (note_index < 0 || note_index > 11) {
    return -1.0;
  }

  if (octave < 1 || octave > 5) {
    return -1.0;
  }

  return frequencies[note_index][octave - 1];
}
