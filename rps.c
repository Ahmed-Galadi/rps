#include <stdio.h>
#include <stdlib.h>
#include <time.h>

# define ROCK "\
    _______\n\
---'   ____)\n\
      (_____)\n\
      (_____)\n\
      (____)\n\
---.__(___)\n\
"
# define PAPER "\
    _______\n\
---'   ____)____\n\
          ______)\n\
          ________)\n\
          ______)\n\
---.________)\n\
"
# define SCISSOR "\
    _______\n\
---'   ____)____\n\
          ______)\n\
       __________)\n\
      (____)\n\
---.__(___)\n\
"

# define LOSER_MSG "\
 ▄· ▄▌      ▄• ▄▌    ▄▄▌        .▄▄ · ▄▄▄▄▄\n\
▐█▪██▌▪     █▪██▌    ██•  ▪     ▐█ ▀. •██  \n\
▐█▌▐█▪ ▄█▀▄ █▌▐█▌    ██▪   ▄█▀▄ ▄▀▀▀█▄ ▐█.▪\n\
 ▐█▀·.▐█▌.▐▌▐█▄█▌    ▐█▌▐▌▐█▌.▐▌▐█▄▪▐█ ▐█▌·\n\
  ▀ •  ▀█▄▀▪ ▀▀▀     .▀▀▀  ▀█▄▀▪ ▀▀▀▀  ▀▀▀ \n\
"

# define WINNER_MSG "\
██╗   ██╗ ██████╗ ██╗   ██╗    ██╗    ██╗ ██████╗ ███╗   ██╗\n\
╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║    ██║██╔═══██╗████╗  ██║\n\
 ╚████╔╝ ██║   ██║██║   ██║    ██║ █╗ ██║██║   ██║██╔██╗ ██║\n\
  ╚██╔╝  ██║   ██║██║   ██║    ██║███╗██║██║   ██║██║╚██╗██║\n\
   ██║   ╚██████╔╝╚██████╔╝    ╚███╔███╔╝╚██████╔╝██║ ╚████║\n\
   ╚═╝    ╚═════╝  ╚═════╝      ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═══╝\n\
"

# define DRAW_MSG "\
┳┓┳┓┏┓┓ ┏\n\
┃┃┣┫┣┫┃┃┃\n\
┻┛┛┗┛┗┗┻┛\n\
"

# define INVALID_INPUT_MSG "\
⠁⡼⠋⠀⣆⠀⠀⣰⣿⣫⣾⢿⣿⣿⠍⢠⠠⠀⠀⢀⠰⢾⣺⣻⣿⣿⣿⣷⡀⠀\n\
⣥⠀⠀⠀⠁⠀⠠⢻⢬⠁⣠⣾⠛⠁⠀⠀⠀⠀⠀⠀⠀⠐⠱⠏⡉⠙⣿⣿⡇⠀\n\
⢳⠀⢰⡖⠀⠀⠈⠀⣺⢰⣿⢻⣾⣶⣿⣿⣶⣶⣤⣤⣴⣾⣿⣷⣼⡆⢸⣿⣧⠀ ____ ____ ____ ____ ____  \n\
⠈⠀⠜⠈⣀⣔⣦⢨⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣅⣼⠛⢹⠀||W |||r |||o |||n |||g ||\n\
⠀⠀⠀⠀⢋⡿⡿⣯⣭⡟⣟⣿⣿⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⡘⠀||__|||__|||__|||__|||__|| \n\
⡀⠐⠀⠀⠀⣿⣯⡿⣿⣿⣿⣯⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⣉⢽⣿⡆⠀⠀|/__\\|/__\\|/__\\|/__\\|/__\\|  \n\
⢳⠀⠄⠀⢀⣿⣿⣿⣿⣿⣿⣿⠙⠉⠉⠉⠛⣻⢛⣿⠛⠃⠀⠐⠛⠻⣿⡇⠀⠀ ____ ____ ____ ____ ____ _________ ____ \n\
⣾⠄⠀⠀⢸⣿⣿⡿⠟⠛⠁⢀⠀⢀⡄⣀⣠⣾⣿⣿⡠⣴⣎⣀⣠⣠⣿⡇⠀⠀||I |||n |||p |||u |||t |||       |||! ||\n\
⣧⠀⣴⣄⣽⣿⣿⣿⣶⣶⣖⣶⣬⣾⣿⣾⣿⣿⣿⣿⣽⣿⣿⣿⣿⣿⣿⡇⠀⠀||__|||__|||__|||__|||__|||_______|||__||\n\
⣿⣶⣈⡯⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⣹⢧⣿⣿⣿⣄⠙⢿⣿⣿⣿⠇⠀⠀|/__\\|/__\\|/__\\|/__\\|/__\\|/_______\\|/__\\|\n\
⠹⣿⣿⣧⢌⢽⣻⢿⣯⣿⣿⣿⣿⠟⣠⡘⠿⠟⠛⠛⠟⠛⣧⡈⠻⣾⣿⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⠀⠈⠉⣷⡿⣽⠶⡾⢿⣿⣿⣿⢃⣤⣿⣷⣤⣤⣄⣄⣠⣼⡿⢷⢀⣿⡏⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠀⠰⠛⠻⢿⣿⠿⠿⠟⡿⠿⢿⣿⠿⠿⣿⠃⠀⠟⠛⠿⣿⣿⣿⣿⣿⣿\n\
⠀⠀⢀⣿⣷⠌⣈⣏⣝⠽⡿⣷⣾⣏⣀⣉⣉⣀⣀⣀⣠⣠⣄⡸⣾⣿⠃⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⣴⡄⠀⠘⡇⠀⣤⣤⡇⠀⣼⣿⠀⢠⡏⠀⢠⣦⠀⠀⣽⣿⣿⣿⣿⣿\n\
⠀⣰⡿⣿⣧⡐⠄⠱⣿⣺⣽⢟⣿⣿⢿⣿⣍⠉⢀⣀⣐⣼⣯⡗⠟⡏⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠀⠀⠛⠃⠀⡼⠀⠀⣿⣿⠀⠀⠛⠃⠀⢸⠁⠀⣼⡏⠀⢠⣿⣿⣿⣿⣿⣿\n\
⣰⣿⠀⣿⣿⣴⡀⠂⠘⢹⣭⡂⡚⠿⢿⣿⣿⣿⡿⢿⢿⡿⠿⢁⣴⣿⣷⣶⣦⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣶⣶⣶⣾⣷⣶⣾⣿⣿⣷⣶⣶⣶⣶⣿⣶⣶⣿⣷⣶⣾⣿⣿⣿⣿⣿⣿\n\n\
PLEASE ENTER \"rock\" or \"paper\" or \"scissor\"\
"

int is_strequ(char *s1, char *s2)
{
	int		i;

	i = -1;
	while (s1[++i])
		if (s1[i] != s2[i])
			return (0);
	return (1);
}

char *choice_to_ascii(char *choice)
{
	if (is_strequ(choice, "rock"))
		return (ROCK);
	if (is_strequ(choice, "paper"))
		return (PAPER);
	if (is_strequ(choice, "scissor"))
		return (SCISSOR);
	return (NULL);
}
void loser_message(char *player_choice, char *mchn_choice)
{
	printf("\033[0;31m");
	printf("\n%s", LOSER_MSG);
	printf("\033[0;33m");
	printf("\nYOU CHOOSE:\n%s\n", choice_to_ascii(player_choice));
	printf("AGAINST:\n%s", choice_to_ascii(mchn_choice));
	printf("\033[0m");
}

void draw_message(char *player_choice, char *mchn_choice)
{
	printf("\033[0;34m");
	printf("\n%s", DRAW_MSG);
	printf("\033[0;35m");
	printf("\nYOU CHOOSE:\n%s\n", choice_to_ascii(player_choice));
	printf("AGAINST:\n%s", choice_to_ascii(mchn_choice));
	printf("\033[0m");
}

void winner_message(char *player_choice, char *mchn_choice)
{
	printf("\033[0;32m");
	printf("\n%s", WINNER_MSG);
	printf("\033[0;36m");
	printf("\nYOU CHOOSE:\n%s\n", choice_to_ascii(player_choice));
	printf("AGAINST:\n%s", choice_to_ascii(mchn_choice));
	printf("\033[0m");
}

int generate_random(void)
{
	int		ran_num;

	srand(time(NULL));
	ran_num = rand();
	return (ran_num % 3);
}


char *mchn_translate(int mchn_choice)
{
	if (mchn_choice == 0)
		return ("rock");
	if (mchn_choice == 1)
		return ("scissor");
	if (mchn_choice == 2)
		return ("paper");
	return (NULL);
}

void rps(char *player_choice, int mchn_choice)
{
	char *traslated_mchn;

	traslated_mchn = mchn_translate(mchn_choice);
	if (is_strequ(player_choice, "rock") && is_strequ(traslated_mchn, "scissor"))
		winner_message(player_choice, traslated_mchn);
	if (is_strequ(player_choice, "rock") && is_strequ(traslated_mchn, "paper"))
		loser_message(player_choice, traslated_mchn);
	if (is_strequ(player_choice, "scissor") && is_strequ(traslated_mchn, "paper"))
		winner_message(player_choice, traslated_mchn);
	if (is_strequ(player_choice, "scissor") && is_strequ(traslated_mchn, "rock"))
		loser_message(player_choice, traslated_mchn);
	if (is_strequ(player_choice, "paper") && is_strequ(traslated_mchn, "rock"))
		winner_message(player_choice, traslated_mchn);
	if (is_strequ(player_choice, "paper") && is_strequ(traslated_mchn, "scissor"))
		loser_message(player_choice, traslated_mchn);
	if (is_strequ(player_choice, traslated_mchn))
		draw_message(player_choice, traslated_mchn);
	
}

int main(int argc, char *argv[])
{
	if (argc != 2 || (!is_strequ(argv[1], "rock") && !is_strequ(argv[1], "paper") && !is_strequ(argv[1], "scissor")))
	{
		printf("\033[0;31m");
		printf("%s\n", INVALID_INPUT_MSG);
		printf("\033[0m");
	}
	else
		rps(argv[1], generate_random());
	return (0);
}