#include "AI.hpp"

Node::Node( int depth, Board board_, bool side_, bool color_, Move move_ ) {
    color = color_;
    board = board_;
    side = side_;
    move = move_;
    value = 0;
    if ( depth == 0 || board.checkState( side ) != 0 )
        value = board.evaluateBoard( side, color );
    else {
        for ( auto& m : board.getViableMoves( side ) ) {
            Board tmp( board );
            tmp.move( m );
            childs.emplace_back( depth-1, tmp, !side, color, m );
        }
    }
}

int minimax( Node& node, int depth, bool isMaximizingPlayer, int alpha, int beta )
{
    if ( node.childs.size() == 0 )
        return node.value;

    int value, bestVal;

    if ( isMaximizingPlayer ) {
        bestVal = -100000;
        for ( auto& child : node.childs ) {
            value = minimax(child, depth+1, false, alpha, beta);
            bestVal = std::max( bestVal, value);
            if ( bestVal == value && depth == 0 )
                node.move = child.move;
            alpha = std::max( alpha, bestVal);
            if ( beta <= alpha )
                break;
        }
        return bestVal;

    } else {
        bestVal = 100000;
        for ( auto& child : node.childs ) {
            value = minimax(child, depth+1, true, alpha, beta);
            bestVal = std::min( bestVal, value );
            if ( bestVal == value && depth == 0 )
                node.move = child.move;
            beta = std::min( beta, bestVal);
            if ( beta <= alpha )
                break;
        return bestVal;
        }
    }
}

Move AI::getBestMove( int maxdepth, Board board, bool side ) {
    auto root = std::make_unique<Node>( maxdepth, board, side, side );
		// minimax( *root, 0, true, -100000, 100000 );
    minimax( *root, 0, true, -100000, 100000 );
    return root -> move;
}
