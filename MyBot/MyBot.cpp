#include <dpp/dpp.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>

//Application ID: 1108483443559518369

//Public Key: 8aaf8931e9879ce0e791d487b5fbf5c1b43fe3d9f1c49f112affe92858191ef7

//Client ID: 1108483443559518369

//Invite Email: https://discord.com/api/oauth2/authorize?client_id=1108483443559518369&permissions=534723950656&scope=bot

//Bot Token: MTEwODQ4MzQ0MzU1OTUxODM2OQ.GFd8lN.a1hI4hiF6_3eK-BzKY05PW03pnaAQncoutCgo8

const std::string    BOT_TOKEN = "MTEwODQ4MzQ0MzU1OTUxODM2OQ.GFd8lN.a1hI4hiF6_3eK-BzKY05PW03pnaAQncoutCgo8";
const dpp::snowflake  MY_GUILD_ID = 1108483443559518369;
/*
int test1()
{
    struct std::tm a = { 0,0,0,24,5,104 }; /* June 24, 2004 
    struct std::tm b = { 0,0,0,5,6,104 }; /* July 5, 2004 
    std::time_t x = std::mktime(&a);
    std::time_t y = std::mktime(&b);
    if (x != (std::time_t)(-1) && y != (std::time_t)(-1))
    {
        double difference = std::difftime(y, x) / (60 * 60 * 24);
        std::cout << std::ctime(&x);
        std::cout << std::ctime(&y);
        std::cout << "difference = " << difference << " days" << std::endl;
    }
    return 0;
}
*/

time_t dateToTimeT(int month, int day, int year) {
    // january 5, 2000 is passed as (1, 5, 2000)
    tm tmp = tm();
    tmp.tm_mday = day;
    tmp.tm_mon = month - 1;
    tmp.tm_year = year - 1900;
    return mktime(&tmp);
}

time_t badTime() {
    return time_t(-1);
}

time_t now() {
    return time(0);
}

int main() {

    dpp::cluster bot(BOT_TOKEN);

    bot.on_log(dpp::utility::cout_logger());

    //test1();

    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("test  ");
        }
        if (event.command.get_command_name() == "ping2") {
            event.reply("test2  ");
        }
        if (event.command.get_command_name() == "bruh") {
            time_t date1 = dateToTimeT(6, 28, 2023);
            time_t date2 = dateToTimeT(1, 1, 2001);

            if ((date1 == badTime()) || (date2 == badTime())) {
                std::cerr << "unable to create a time_t struct" << std::endl;
                return EXIT_FAILURE;
            }

            auto end = std::chrono::system_clock::now();
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            double sec = difftime(date1, end_time);
            long days = static_cast<long>(sec / (60 * 60 * 24));
            std::string s = "Noch so viele Tage habt ihr " + days;
            event.reply("Noch so viele Tage habt ihr ");
        }

        if (event.command.get_command_name() == "blep") {
            /* Fetch a parameter value from the command parameters */
            std::string animal = std::get<std::string>(event.get_parameter("animal"));
            /* Reply to the command. There is an overloaded version of this
            * call that accepts a dpp::message so you can send embeds.
            */
            event.reply(std::string("Blep! You chose") + animal);
        }
        /*
        if (event.command.get_command_name() == "Blep") {
            std::string animal = std::get<std::string>(event.get_parameter("animal"));

                event.reply(std::string("Blep! You chose") + animal);
        }
        */
        });

    bot.on_ready([&bot](const dpp::ready_t& event) {
 
        if (dpp::run_once<struct register_bot_commands>()) {

        dpp::slashcommand newcommand("blep", "Send a random adorable animal photo", bot.me.id);
            newcommand.add_option(
                dpp::command_option(dpp::co_string, "animal", "The type of animal", true).
                add_choice(dpp::command_option_choice("Dog", std::string("animal_dog"))).
                add_choice(dpp::command_option_choice("Cat", std::string("animal_cat"))).
                add_choice(dpp::command_option_choice("Penguin", std::string("animal_penguin")
                )
                )
            );
            /*
            dpp::slashcommand newcommand("blep", "Send a random adorable animal photo", bot.me.id);
            newcommand.add_option(
                dpp::command_option(dpp::co_string, "animal", "The type of animal", true).
                add_choice(dpp::command_option_choice("Dog", std::string("animal_dog"))).
                add_choice(dpp::command_option_choice("Cat", std::string("animal_cat"))).
                add_choice(dpp::command_option_choice("Penguin", std::string("animal_penguin")
                )
                )
            );
            */
            bot.global_command_create(newcommand);

            dpp::slashcommand Doomsdaytest("Wann", "Gibt an wann die Klausrenphase anfängt ", bot.me.id);
            
            bot.global_command_create(Doomsdaytest);
           
            bot.global_command_create(
                dpp::slashcommand("ping", "Ping pong!", bot.me.id)
            );

            bot.global_command_create(
                dpp::slashcommand("ping2", "Ping pong!", bot.me.id)
            );

            bot.global_command_create(
                dpp::slashcommand("bruh", "Gibt an wann die Klausrenphase anfängt ", bot.me.id)
            );

           
        }
        });

    bot.start(dpp::st_wait);

    return 0;   
}
