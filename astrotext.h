typedef struct {
	u08		status; // 1 for alive 0 for dead 2 for win
	u08		shipLoc; // location of ships tail
	u16		asteroidsTop;
	u16		asteroidsBottom;
	u16		userProjectilesTop;
	u16		userProjectilesBottom;
} Game;

void newGame(Game *game);
void renderFrame(Game *game);