typedef struct {
	u08		status; 				// status != 0 is active, status = 0 is inactive
	u08		speed;					// FPS
	u08		shipLoc; 				// location of ships tail
	u16		asteroidsTop;			// bits denote asteroid locations, 1 for asteroid, 0 for no asteroid
	u16		asteroidsBottom;
	u16		userProjectilesTop;
	u16		userProjectilesBottom;
} Game;

void newGame(Game *game);
void renderFrame(Game *game);