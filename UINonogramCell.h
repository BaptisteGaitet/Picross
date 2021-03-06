#ifndef UI_NONOGRAM_CELL_H
#define UI_NONOGRAM_CELL_H

#include "UIElement.h"
#include "TextureManager.h"
#include "MouseManager.h"
#include "AudioManager.h"

class UINonogramCell :
	public UIElement
{
private:
	enum CellState {grassIdle, grassHovered, grassPressed, ground, flaggedIdle, flaggedHovered, flaggedPressed, black, white};
	CellState state;
	bool filled;
	bool mistake;
public:
	UINonogramCell(std::string _id, sf::IntRect _bounds, int _drawOrder);

	void update();
	void draw(sf::RenderWindow* window);
	void setFilled(bool _filled);
	bool getFilled();
	bool isFound();
	bool getMistake();
	void setBlackWhite(bool _val);
	bool isBlackWhite();

	~UINonogramCell();
};

#endif