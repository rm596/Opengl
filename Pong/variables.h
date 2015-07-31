#ifndef variables

// window size and update rate (60 fps)
int width = 500;
int height = 200;
int interval = 1000 / 60;

// score
int score_left = 0;
int score_right = 0;

// rackets in general
int racket_width = 10;
int racket_height = 80;
int racket_speed = 3;

// left racket position
float racket_left_x = 10.0f;
float racket_left_y = 50.0f;

// right racket position
float racket_right_x = 480;
float racket_right_y = 50;

// ball
float ball_pos_x = width / 2;
float ball_pos_y = height / 2;

float ball_dir_x = -1.0f;
float ball_dir_y = 0.0f;

int ball_size = 8;
int ball_speed = 2;

#endif // !extra
