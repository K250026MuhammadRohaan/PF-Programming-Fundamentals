#include <stdio.h>

void calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets, int gravitationalZones[], int numZones) {
    if (fuel <= 0) {
        printf("Planet %d: Fuel Remaining = 0\n", planet);
        printf("Mission failed. Fuel exhausted.\n");
        return;
    }
    if (planet > totalPlanets) {
        printf("Mission completed! Fuel remaining: %d\n", fuel);
        return;
    }

    fuel -= consumption;

    for (int i = 0; i < numZones; i++) {
        if (gravitationalZones[i] == planet) {
            fuel += recharge;
            break;
        }
    }

    if (planet % 4 == 0) fuel += solarBonus;

    if (fuel < 0) fuel = 0;
    printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);

    calculateFuel(fuel, consumption, recharge, solarBonus, planet + 1, totalPlanets, gravitationalZones, numZones);
}

int main() {
    int totalPlanets, initialFuel, consumption, recharge, solarBonus, numZones;

    printf("Enter total number of planets: ");
    scanf("%d", &totalPlanets);
    printf("Enter initial fuel: ");
    scanf("%d", &initialFuel);
    printf("Enter fuel consumption per planet: ");
    scanf("%d", &consumption);
    printf("Enter fuel gained in gravitational zones: ");
    scanf("%d", &recharge);
    printf("Enter solar recharge bonus: ");
    scanf("%d", &solarBonus);
    printf("Enter number of gravitational zones: ");
    scanf("%d", &numZones);

    int gravitationalZones[numZones];
    if (numZones > 0) {
        printf("Enter planets with gravitational zones (space-separated): ");
        for (int i = 0; i < numZones; i++) scanf("%d", &gravitationalZones[i]);
    }

    printf("\n--- Fuel Simulation ---\n");
    calculateFuel(initialFuel, consumption, recharge, solarBonus, 1, totalPlanets, gravitationalZones, numZones);

    return 0;
}