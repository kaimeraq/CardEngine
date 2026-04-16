#pragma once

#include "Renderer/Widget.h"
#include "Renderer/CardRenderer.h"
#include "Cards/Card.h"
#include "Cards/Hand.h"
#include "Cards/Deck.h"

class CardWidget : public Widget
{
    const Card* m_card = nullptr;

public:
    CardWidget(const Card* card, CardRenderer* renderer)
        : Widget(renderer), m_card(card) {}

    void Draw() const override
    {
        if (m_card && GetRenderer())
        {
            static_cast<CardRenderer*>(GetRenderer())->DisplayCard(*m_card);
        }
    }
};

class HandWidget : public Widget
{
    const Hand* m_hand = nullptr;

public:
    HandWidget(const Hand* hand, HandRenderer* renderer)
        : Widget(renderer), m_hand(hand) {
    }

    void Draw() const override
    {
        if (m_hand && GetRenderer())
        {
            static_cast<HandRenderer*>(GetRenderer())->DisplayHand(*m_hand);
        }
    }
};

class DeckWidget : public Widget
{
    const Deck* m_deck = nullptr;

public:
    DeckWidget(const Deck* deck, DeckRenderer* renderer)
        : Widget(renderer), m_deck(deck) {
    }

    void Draw() const override
    {
        if (m_deck && GetRenderer())
        {
            static_cast<DeckRenderer*>(GetRenderer())->DisplayDeck(*m_deck);
        }
    }
};