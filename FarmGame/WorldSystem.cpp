#include "WorldSystem.h"
#include <iostream>
#include <fstream>

using namespace std;
WorldSystem::WorldSystem() : days(1) {}


void WorldSystem::ProccessDay(RenderingEngine* renderEngine, Farmer* player, Prices* todaysPrices, bool& isUserQuiting) const
{
    if (days != 1)
    {
        todaysPrices->DailyPriceChange();
    }


    while (true)
    {
        system("CLS");
        renderEngine->DisplayDailyOptions(days, player);

        int input;
        cin >> input;

        switch (input)
        {
        // Sell Products
        case 1:
            this->SellScreen(renderEngine, player, todaysPrices);
            break;

        // Buy Animals
        case 2:
            this->PurchaseScreen(renderEngine, player, todaysPrices);
            break;

        // Sleep
        case 3:
            return;
            break;

        // Save and Quit
        case 4:
            isUserQuiting = true;
            return;
            break;

        default:
            cout << "Wrong command. Try again." << '\n';
            break;
        }
    }
}


void WorldSystem::SaveData(std::ofstream& outSaveFile) const
{
    outSaveFile << days << '\n';
}


void WorldSystem::LoadData(std::ifstream& saveFile)
{
    saveFile >> days;
}

void WorldSystem::FinishDay(RenderingEngine* renderEngine, Farmer* player, Prices* todaysPrices)
{
    player->FinishDay(days);
    renderEngine->DayEndScreen();

    // Check if the week has ended
    if (days % 7 == 0)
    {
        todaysPrices->WeeklyPriceChange();
    }
    todaysPrices->DailyPriceChange();

    days++;

}


void WorldSystem::SellScreen(RenderingEngine* renderEngine, Farmer* player, Prices* todaysPrices) const
{
    system("CLS");
    renderEngine->SellProductScreen(player, todaysPrices);

    while (true)
    {
        int input;
        int amount;
        cin >> input;

        // for when the user enters something other than int
        if (cin.fail()) {
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid Input" << '\n';
            continue; // Restart the loop
        }

        if (input >= 1 && input <= 4)
        {
            cout << "And how much?" << '\n';
            cin >> amount;

            if (amount <= 0)
            {
                while (true)
                {
                    cout << "And how many?" << '\n';
                    cin >> amount;
                    if (amount <= 0)
                    {
                        cout << "Invalid amount: " << amount << '\n';
                        continue;
                    }
                    break;
                }
            }
        }
        switch (input)
        {
        case 1:
            player->SellProduct(Product::Eggs, amount, renderEngine, todaysPrices);
            break;
        case 2:
            player->SellProduct(Product::Milk, amount, renderEngine, todaysPrices);
            break;
        case 3:
            player->SellProduct(Product::Wool, amount, renderEngine, todaysPrices);
            break;
        case 4:
            player->SellProduct(Product::CrocSkin, amount, renderEngine, todaysPrices);
            break;
        case 5:
            return;
            break;
        default:
            cout << "Invalid Input" << '\n';
            break;
        }
    }
}

void WorldSystem::PurchaseScreen(RenderingEngine * renderEngine, Farmer * player, Prices * todaysPrices) const
{
    system("CLS");
    renderEngine->BuyAnimalsScreen(player, todaysPrices);
    while (true)
    {
        int input;
        int amount;
        cin >> input;

        // for when the user enters something other than int
        if (cin.fail()) {
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid Input" << '\n';
            continue;
        }

        if (input >= 1 && input <= 4)
        {
            while (true)
            {
                cout << "And how many?" << '\n';
                cin >> amount;
                if (amount <= 0)
                {
                    cout << "Invalid amount: " << amount << '\n';
                    continue;
                }
                break;
            }
        }

        switch (input)
        {
        case 1:
            player->PurchaseAnimal(AnimalTypes::Chicken, amount, renderEngine, todaysPrices);
            break;
        case 2:
            player->PurchaseAnimal(AnimalTypes::Cow, amount, renderEngine, todaysPrices);
            break;
        case 3:
            player->PurchaseAnimal(AnimalTypes::Sheep, amount, renderEngine, todaysPrices);
            break;
        case 4:
            player->PurchaseAnimal(AnimalTypes::Crocodile, amount, renderEngine, todaysPrices);
            break;
        case 5:
            return;
            break;
        default:
            cout << "Invalid Input" << '\n';
            break;
        }
    }
}
