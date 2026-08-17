#ifndef SCORE_HPP
#define SCORE_HPP

class Score
{
public:
    void scoreLeft() { ++left_; }
    void scoreRight() { ++right_; }
    int left() const { return left_; }
    int right() const { return right_; }

private:
    int left_{0};
    int right_{0};
};

#endif // SCORE_HPP
