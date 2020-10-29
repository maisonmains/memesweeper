#pragma once

#include "Graphics.h"
#include "Sound.h"
#include "SelectionMenu.h"
#include <random>

class MemeField
{
public:
	enum class State
	{
		Fucked,
		Winrar,
		Memeing
	};
private:
	class Tile
	{
	public:
		enum class State
		{
			Hidden,
			Flagged,
			Revealed
		};
	public:
		void SpawnMeme();
		bool HasMeme() const;
		void Draw( const Vei2& screenPos,MemeField::State fucked,Graphics& gfx ) const;
		void Reveal();
		bool IsRevealed() const;
		void ToggleFlag();
		bool IsFlagged() const;
		bool HasNoNeighborMemes() const;
		void SetNeighborMemeCount( int memeCount );
	private:
		State state = State::Hidden;
		bool hasMeme = false;
		int nNeighborMemes = -1;
	};
public:
	MemeField();
	void InitState( );
	void InitField( const Vei2& center, const SelectionMenu::Size& size );
	void Draw( Graphics& gfx ) const;
	RectI GetRect() const;
	void OnRevealClick( const Vei2& screenPos );
	void OnFlagClick( const Vei2& screenPos );
	State GetState() const;
	~MemeField();
private:
	
	void GenDims( const SelectionMenu::Size& size );
	void SpawnMemes( );
	void SetNeighbors( );
	void RevealTile( const Vei2& gridPos );
	Tile& TileAt( const Vei2& gridPos );
	const Tile& TileAt( const Vei2& gridPos ) const;
	Vei2 ScreenToGrid( const Vei2& screenPos );
	int CountNeighborMemes( const Vei2& gridPos );
	bool GameIsWon() const;
	
private:
	int width = 0;
	int height = 0;
	static constexpr int borderThickness = 10;
	static constexpr Color borderColor = Colors::Blue;
	Sound sndLose = Sound( L"spayed.wav" );
	Vei2 topLeft;
	State state = State::Memeing;
	Tile* field = new Tile[ width * height ];
};