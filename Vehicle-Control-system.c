#include <stdio.h>

// Vehicle state enum
enum vehicle_state
{
    ENGINE_OFF = 0,
    ENGINE_ON,
};

// Vehicle structure
struct vehicle
{
    enum vehicle_state state;
    int speed;
    int room_temperature;
    int engine_temperature;
    int ac_state;
    int engine_temperature_controller_state;
};

char u8_gflag1 = 0;
char u8_gflag2 = 0;
char u8_gflag3 = 0;
char u8_gflag4 = 0;
char u8_gflag5 = 0;

// Function to print the current vehicle state
void print_vehicle_state(struct vehicle vehicle)
{
    printf("_____________________________________________________\n\n");
    printf("\tThe current vehicle state: \n\n");
    printf("\t*******************\n\n");
    printf("Engine state: %s\n", vehicle.state == ENGINE_ON ? "ON" : "OFF");
    printf("AC: %s\n", vehicle.ac_state == 1 ? "ON" : "OFF");
    printf("Vehicle speed: %d km/hr\n", vehicle.speed);
    printf("Room temperature: %d degrees Celsius\n", vehicle.room_temperature);
    printf("Engine temperature: %d degrees Celsius\n", vehicle.engine_temperature);
    printf("Engine temperature controller state: %s\n", vehicle.engine_temperature_controller_state == 1 ? "ON" : "OFF");
    printf("_____________________________________________________\n\n");
}

void simulate_vehicle_sensors(struct vehicle *vehicle)
{
    // Get the traffic light color from the console
    char traffic_light_color;
    printf("_____________________________________________________\n\n");
    printf("Enter the traffic light color: ");
    scanf(" %c", &traffic_light_color);
    // Set the vehicle speed based on the traffic light color
    switch (traffic_light_color)
    {
    case 'G':
        vehicle->speed = 100;
        u8_gflag1 = 1;
        break;
    case 'O':
        vehicle->speed = 30;
        u8_gflag1 = 1;
        break;
    case 'R':
        vehicle->speed = 0;
        u8_gflag1 = 1;
        break;
    default:
        printf("Invalid traffic light color.\n");
        break;
    }
    // vehicle.state = ENGINE_ON;
}

void room_temperature_vehicle(struct vehicle *vehicle)
{

    // Get the room temperature from the console
    int room_temperature;
    printf("Enter the room temperature: ");
    scanf("%d", &room_temperature);
    u8_gflag2 = 1;
    // Set the AC state based on the room temperature
    if (room_temperature < 10 || room_temperature > 30)
    {
        vehicle->ac_state = 1;
        vehicle->room_temperature = 20;
    }
    else
    {
        vehicle->ac_state = 0;
        vehicle->room_temperature = room_temperature;
    }
}

void engine_temperature_vehicle(struct vehicle *vehicle)
{

    // Get the engine temperature from the console
    int engine_temperature;
    printf("Enter the engine temperature: ");
    scanf("%d", &engine_temperature);
    u8_gflag3 = 1;
    // Set the engine temperature controller state based on the engine temperature
    if (engine_temperature < 100 || engine_temperature > 150)
    {
        vehicle->engine_temperature_controller_state = 1;
        vehicle->engine_temperature = 125;
    }
    else
    {
        vehicle->engine_temperature_controller_state = 0;
    }
}

void vehicle_spead(struct vehicle *vehicle)
{
    // Adjust the room temperature based on the vehicle speed
    if (vehicle->speed == 30)
    {
        vehicle->room_temperature = (vehicle->room_temperature * 5 / 4) + 1;
        vehicle->engine_temperature = (vehicle->engine_temperature * 5 / 4) + 1;
        vehicle->ac_state = 1;
        vehicle->engine_temperature_controller_state = 1;
    }
}

int main()
{
    // Initialize the vehicle state
    struct vehicle vehicle = {
        .state = ENGINE_OFF,
    };

    // Display the welcome message
    printf("Welcome to the vehicle control system!\n\n");
    printf("_____________________________________________________\n\n");
    // Start the main loop
    while (1)
    {
        // Ask the user what they want to do
        printf("What do you want to do?\n");
        printf("(1) Turn on the vehicle engine\n");
        printf("(2) Turn off the vehicle engine\n");
        printf("(3) Quit the system\n");
        printf("_____________________________________________________\n\n");
        printf("Enter your choice: ");

        // Get the user's choice
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            // Turn on the vehicle engine
            vehicle.state = ENGINE_ON;
            printf("The vehicle engine has been turned on.\n");

            // Display the sensors set menu
            while (vehicle.state == ENGINE_ON)
            {

                printf("_____________________________________________________\n\n");
                printf("Sensors set menu:\n");
                printf("(1) Turn off the engine\n");
                printf("(2) Set the traffic light color\n");
                printf("(3) Set the room temperature\n");
                printf("(4) Set the engine temperature\n");
                printf("_____________________________________________________\n\n");
                printf("Enter your choice: ");
                // Get the user's choice
                int sensor_set_choice;
                scanf("%d", &sensor_set_choice);
                // Perform the selected action
                switch (sensor_set_choice)
                {
                case 1:
                    // Turn off the engine
                    vehicle.state = ENGINE_OFF;
                    printf("The vehicle engine has been turned off.\n");
                    break;
                case 2:
                    // Set the traffic light color
                    simulate_vehicle_sensors(&vehicle);
                    vehicle.state = ENGINE_ON;
                    break;
                case 3:
                    room_temperature_vehicle(&vehicle);
                    break;
                case 4:
                    engine_temperature_vehicle(&vehicle);
                    break;
                default:
                    printf("Invalid choice.\n");
                }
                if (u8_gflag1 == 1 && u8_gflag2 == 1 && u8_gflag3 == 1)
                {
                    vehicle_spead(&vehicle);
                    // Display the current vehicle state
                    print_vehicle_state(vehicle);

                    u8_gflag1 = 0;
                    u8_gflag2 = 0;
                    u8_gflag3 = 0;
                }
            }
            break;
        case 2:
            // Turn off the vehicle engine
            vehicle.state = ENGINE_OFF;
            printf("The vehicle engine has been turned off.\n");
            break;
        case 3:
            // Quit the system
            printf("Goodbye!\n");
            return 0;
        default:
            printf("Invalid choice.\n");
        }
    }
    return 0;
}
