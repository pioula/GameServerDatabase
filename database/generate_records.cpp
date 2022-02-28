#include <iostream>
#include <vector>
#include <random>

#define NUMBER_OF_CHESS_GAMES 1000
#define NUMBER_OF_CHECKERS_GAMES 100

using namespace std;

int main() {
    vector<string> nicks = {"jkd", "magzy", "nepo", "shak", "mvl", "sasha",
                            "hikaru", "fabi", "anish", "firo", "garry",
                            "vishy", "radek", "levon", "boris", "peter",
                            "kramnik", "karpov", "ding", "wesley", "richard",
                            "radja", "leinier", "wang", "vidit", "sam",
                            "xiong", "dubov", "andrey", "vlad", "zbychu",
                            "topalov", "chucky", "tari", "judit", "jorden",
                            "nils", "nodir", "nihal", "arjun", "tang", "danya",
                            "eric", "fedo", "dmitry", "parham", "amin", "haik",
                            "evgeny", "nikita"};

    vector<string> chess = {"1.d4 Nf6 2.Nf3 d5 3.e3 Bf5 4.c4 c6 5.Nc3 e6 6.Bd3 Bxd3 7.Qxd3 Nbd7 8.b3 Bd6 9.O-O O-O 10.Bb2 Qe7 11.Rad1 Rad8 12.Rfe1 dxc4 13.bxc4 e5 14.dxe5 Nxe5 15.Nxe5 Bxe5 16.Qe2 Rxd1 17.Rxd1 Rd8 18.Rxd8+ Qxd8 19.Qd1 Qxd1+ 20.Nxd1 Bxb2 21.Nxb2 b5 22.f3 Kf8 23.Kf2 Ke7",
                            "1.e4 e6 2.d4 d5 3.Nc3 Bb4 4.e5 Ne7 5.a3 Bxc3+ 6.bxc3 b6 7.Qg4 Nf5 8.Bd3 h5 9.Qh3 c5 10.Bxf5 exf5 11.Qg3 Kf8 12.h4 Nc6 13.Bg5 f6 14.exf6 gxf6 15.Be3 Qe7 16.Ne2 Be6 17.O-O Kf7 18.Nf4 Rag8 19.Qf3 Qd7 20.Rad1 c4 21.Rfe1 Rg4 22.g3 Kf8 23.Nxe6+ Qxe6 24.Bh6+ Kf7 25.Rxe6 Kxe6 26.Bf4 Ne7 27.Re1+ Kd7 28.Qe3",
                            "1.d4 d5 2.c4 e6 3.Nc3 Nf6 4.e3 Be7 5.Nf3 O-O 6.Bd3 Nbd7 7.e4 dxe4 8.Nxe4 Nxe4 9.Bxe4 Nf6 10.Bc2 Bb4+ 11.Bd2 Bxd2+ 12.Qxd2 b6 13.O-O Bb7 14.Ne5 Nd7 15.Qd3 g6 16.Nxd7 Qxd7 17.b3 Rad8 18.Rad1 c5 19.dxc5 Qxd3 20.Rxd3 Rxd3 21.Bxd3 bxc5 22.Rd1 Rd8 23.f3 e5 24.Kf2 e4 25.Be2 Rxd1 26.Bxd1 Kf8 27.fxe4 Bxe4 28.a3 a5 29.g3 Ke7 30.Ke3",
                            "1.e4 c5 2.Nf3 Nc6 3.d4 cxd4 4.Nxd4 e5 5.Nb5 d6 6.N1c3 a6 7.Na3 b5 8.Nd5 Nge7 9.c4 Nd4 10.cxb5 Nxd5 11.exd5 Bd7 12.Be3 axb5 13.Bxd4 exd4 14.Qxd4 Be7 15.Nxb5 O-O 16.Nc3 Bf6 17.Qd2 Re8+ 18.Be2 Bxc3 19.Qxc3 Bb5 20.O-O Rxe2 21.Rfe1 Rxe1+ 22.Qxe1 Bc4",
                            "1.e4 e5 2.Nf3 Nf6 3.Nxe5 d6 4.Nf3 Nxe4 5.d4 d5 6.Bd3 Bd6 7.O-O O-O 8.c4 c6 9.Nc3 Nxc3 10.bxc3 Bg4 11.Rb1 b6 12.cxd5 cxd5 13.c4 Nc6 14.cxd5 Nxd4 15.Bxh7+ Kxh7 16.Qxd4 Bxf3 17.Qd3+ f5 18.Qxf3 Be5 19.Ba3 Bd6 20.Bxd6 Qxd6 21.Rbc1 g6 22.Rc6 Qd7 23.Rfc1 Rac8 24.Qh3+",
                            "1.e4 g6 2.d4 Bg7 3.Nc3 d6 4.f4 c5 5.dxc5 Qa5 6.cxd6 Bxc3+ 7.bxc3 Qxc3+ 8.Bd2 Qd4 9.Bd3 Qxd6 10.Bc3 f6 11.Nf3 Nc6 12.Bd2 Qc5 13.Qe2 Nh6 14.h3 O-O 15.Be3 Qc3+ 16.Kf2 Nf7 17.Rhd1 e5 18.Bc4 Qa5 19.Kg1 Kg7 20.Rab1 Qc7 21.Bc5 Re8 22.Bxf7 Qxf7 23.fxe5 fxe5 24.Ng5 Qxa2 25.Qf2 Nd8 26.Rf1 Qa6 27.Be7 Be6 28.Qf6+ Kg8 29.Bf8 Qxf1+ 30.Rxf1",
                            "1.d4 d5 2.c4 c6 3.Nc3 Nf6 4.Nf3 e6 5.e3 Nbd7 6.Bd3 dxc4 7.Bxc4 b5 8.Bd3 a6 9.a4 Bb7 10.O-O b4 11.Ne4 Nxe4 12.Bxe4 Nf6 13.Nd2 Nxe4 14.Nxe4 Qd5 15.f3 f5 16.Nf2 Rd8 17.b3 c5 18.Bb2 cxd4 19.Bxd4 e5 20.Bb6 Rd6 21.a5 Qe6 22.Qc2 Be7 23.Qc4 Qxc4 24.bxc4 Kf7 25.Rfc1 Rc8 26.Rab1 Ke6 27.c5 Rd2 28.Rxb4 Bc6 29.Rb3 Bb5 30.Rbc3 Rc6 31.e4 f4 32.Rd1 Rxd1+ 33.Nxd1 Ba4 34.Nb2 Bb5 35.Kf2 Bf8 36.g3 Be7 37.Rc2 g6 38.Ke1 Kd7 39.Kd2 Ke6 40.Nd3 Bg5 41.g4 Be7 42.Nb4 Rc8 43.Nd5 Kd7 44.Kc1 Ba4 45.Rc4 Bb5 46.Rc2 Ba4 47.Rc3 Bb5 48.Kd2 Bh4 49.Rc1 Bf2 50.c6+",
                            "1.e4 e5 2.Nf3 Nf6 3.Nxe5 d6 4.Nf3 Nxe4 5.d4 d5 6.Bd3 Nc6 7.O-O Be7 8.c3 Bg4 9.Nbd2 Nxd2 10.Bxd2 O-O 11.Bf4 Bd6 12.Bxd6 cxd6 13.Re1 Qf6 14.Bc2 Na5 15.Bb3 Nc4 16.Bxc4 dxc4 17.Qe2 b5 18.Qe4 Bxf3 19.Qxf3 Qxf3 20.gxf3 Rfe8 21.Kf1 g5 22.Rxe8+ Rxe8 23.Re1 Rxe1+ 24.Kxe1 Kg7 25.Kf1 Kf6 26.Ke2 Kf5 27.Ke3 d5 28.f4 g4 29.f3 h5",
                            "1.e4 e5 2.Nf3 Nf6 3.d3 d6 4.c3 g6 5.Bg5 Bg7 6.Be2 O-O 7.d4 h6 8.Bxf6 Qxf6 9.dxe5 dxe5 10.O-O Nd7 11.Nbd2 Nc5 12.Qc2 Bg4 13.Rfe1 Rfe8 14.b4 Ne6 15.h3 Bxf3 16.Nxf3 Nf4 17.Bc4 Nxh3+ 18.gxh3 Qxf3 19.Re3 Qh5 20.Qb3 Rf8 21.Rd1 Qg5+ 22.Rg3 Qf6 23.Rdd3 g5 24.Rgf3 Qe7 25.Rf5 Kh8 26.Bxf7 Rad8 27.Rdf3 Rd6 28.Kf1 Qd8 29.Bh5 Rxf5 30.Rxf5 Rc6 31.Rf3 Rd6 32.Rf5 Rd2 33.Rf7 Qd3+ 34.Kg2 Qxe4+ 35.Bf3 Qh4 36.Bxb7 g4 37.Qe6 Qxh3+ 38.Kg1 Rd1+",
                            "1.e4 e5 2.Nf3 Nc6 3.Bb5 f5 4.d3 fxe4 5.dxe4 Nf6 6.O-O d6 7.Nc3 Be7 8.Bg5 Be6 9.Bxf6 Bxf6 10.Nd5 O-O 11.Be2 Qd7 12.c3 Ne7 13.Nxf6+ gxf6 14.Nd2 Qc6 15.Kh1 f5 16.exf5 Nxf5 17.Bf3 d5 18.Qe2 e4 19.Bg4 Rae8 20.Rad1 Bc8 21.Nb3 Qg6 22.Bxf5 Rxf5 23.Qe3 Rh5 24.Rde1 Ree5 25.f3 Qg3 26.Qg1 Rh4",
                            "1.e4 c5 2.Nf3 d6 3.d4 Nf6 4.Nc3 cxd4 5.Nxd4 g6 6.f3 Bg7 7.Be3 O-O 8.Qd2 Nc6 9.Nb3 Be6 10.Bh6 a5 11.Bxg7 Kxg7 12.g4 Ne5 13.Be2 Nc4 14.Bxc4 Bxc4 15.h4 a4 16.Nd4 e5 17.Ndb5 d5 18.g5 Nh5 19.exd5 Nf4 20.O-O-O Ra5 21.Na3 Bxd5 22.Nxd5 Rxd5 23.Qe3 Rxd1+ 24.Rxd1 Qc7 25.Qe4 Qc5 26.Qxb7 Ne2+ 27.Kd2 Qf2 28.Qc7 e4 29.fxe4 Re8 30.e5 Qd4+ 31.Ke1 Qe4 32.Kd2 Rxe5 33.c4 Qf4+ 34.Kc2 Nd4+ 35.Rxd4 Qxd4 36.Qxe5+ Qxe5 37.b4 Qe2+",
                            "1.e4 Nf6 2.Nc3 d5 3.e5 Nfd7 4.d4 c5 5.f4 cxd4 6.Nb5 Nc6 7.Nf3 e6 8.Nbxd4 Be7 9.Be2 O-O 10.O-O Nc5 11.Be3 Bd7 12.c3 a5 13.c4 dxc4 14.Bxc4 a4 15.a3 Na5 16.Be2 Nab3 17.Rb1 Qc7 18.Nxb3 Nxb3 19.Bd3 Rfd8 20.Qe2 Bc6 21.Rbd1 Rd7 22.Qf2 Rad8 23.Bb6 Qxb6 24.Qxb6 Bc5+ 25.Qxc5 Nxc5 26.Be2 Rxd1 27.Rxd1 Rxd1+ 28.Bxd1 Nd3 29.b3 axb3 30.Bxb3 Bxf3 31.gxf3 Nxf4 32.Bc4 Ng6 33.Kf2 Nxe5 34.Bb5 Kf8 35.a4 b6 36.Ke3 Ke7 37.Ke4 Kd6 38.f4 f5+",
                            "1.c4 e5 2.Nc3 Bb4 3.Nd5 Be7 4.Nxe7 Nxe7 5.d4 exd4 6.Qxd4 O-O",
                            "1.e4 Nf6 2.Nc3 d5 3.e5 Ne4 4.Nce2 d4 5.d3 Nc5 6.f4 Nc6 7.Nf3 Bg4 8.Ng3 e6 9.Be2 Be7 10.O-O h5 11.h3 h4 12.Nh1 Bf5 13.Nf2 Qd7 14.c4 f6 15.b3 a5 16.a3 a4 17.b4 Nb3 18.Rb1 Nxc1 19.Rxc1 fxe5 20.b5 Na5 21.Nxe5 Qd6 22.Bh5+ g6 23.Nxg6 O-O-O 24.Nxh8 Rxh8 25.Ne4 Qxa3 26.Ra1 Qb3 27.Rxa4 Rxh5 28.Qxh5 Qxa4 29.Qe8+ Bd8 30.Nc5 Qa3 31.Qd7+ Kb8 32.Qxd8+ Ka7 33.Qxc7",
                            "1.Nf3 Nf6 2.g3 b6 3.Bg2 Bb7 4.O-O c5 5.d3 e6 6.e4 d6 7.Re1 Be7 8.c4 O-O 9.Nc3 Nbd7 10.d4 cxd4 11.Nxd4 Qb8 12.f4 Rc8 13.b3 Bf8 14.Be3 a6 15.Rc1 Ra7 16.Bf2 Ba8 17.f5 Re8 18.g4 exf5 19.Nxf5 Nc5 20.Ng3 Rae7 21.Nd5 Bxd5 22.exd5 Rxe1+ 23.Bxe1 Rxe1+ 24.Qxe1 Nd3 25.Qd1 Nxc1 26.g5 Nxa2 27.gxf6 Nb4 28.fxg7 Bxg7 29.Be4 Qe8 30.Qg4 Kh8 31.Kf1 Qd8 32.Nh5 Be5 33.Qf5 Qg8 34.Nf6 Bxf6 35.Qxf6+ Qg7 36.Qd8+ Qg8 37.Qxd6 a5 38.Qxb6 Qe8 39.Qh6",
                            "1.c4 Nf6 2.Nc3 c5 3.Nf3 Nc6 4.g3 g6 5.Bg2 Bg7 6.O-O O-O 7.d3 d6 8.Rb1 Rb8 9.a3 a6 10.b4 cxb4 11.axb4 b5 12.cxb5 axb5 13.h3 Bd7 14.Bd2 Ne8 15.Ne4 Nf6 16.Nxf6+ Bxf6 17.Bh6 Re8 18.Ng5 Nd4 19.Ne4 Bh8 20.Qd2 Rc8 21.e3 Nf5 22.Bg5 h6 23.g4 hxg5 24.gxf5 Bxf5 25.Nxg5 Bc3 26.Qe2 Bf6 27.Ne4 Bxe4 28.Bxe4 Kg7 29.Rfc1 Qd7 30.Bg2 Rh8 31.d4 Rh5 32.Qf3 Rch8 33.Qg4 e6 34.Qf3 d5 35.Qe2 Rg5 36.f4 Rg3 37.Kh2 Bh4 38.Rg1 Rc8 39.Bf1 Rxg1 40.Kxg1 Be7 41.Qd2 Qc6 42.Kf2 Qa6 43.Bd3 Qa3 44.Bxb5 Rb8 45.Be2 Rxb4 46.Rxb4 Bxb4 47.Qd1 Qb2 48.Kf3 Bd2 49.Qf1 Qc3 50.Bd3 Qc1 51.Qxc1 Bxc1",
                            "1.e4 e5 2.Nf3 Nc6 3.Bb5 Nf6 4.Qe2 a6 5.Ba4 Be7 6.O-O b5 7.Bb3 O-O 8.c3 d6 9.h3 Bb7 10.d4 Re8 11.a4 Na5 12.Bc2 Bf8 13.dxe5 dxe5 14.Bg5 Nc4 15.b3 Nd6 16.Rd1 Qe7 17.Nbd2 Bc6 18.Nh2 Qe6 19.a5 b4 20.c4 Nb7 21.Bxf6 Qxf6 22.Ng4 Qe6 23.Ne3 Bc5 24.Nd5 Rac8 25.Nf3 Nd6 26.Rd2 f6 27.Rad1 Bb7 28.Kh1 Nf7 29.Nh4 Red8 30.Nf5 g6 31.Qg4 Kh8 32.Nh6 Qxg4 33.Nxg4 Bxd5 34.cxd5 Kg7 35.Bd3 Rd6 36.Rc2 Bd4 37.Rdc1 Bc3 38.Ne3 c6 39.Bxa6 Rc7 40.Bc4 cxd5 41.Nxd5 Rc5 42.a6 Rdc6 43.Ra2",
                            "1.e4 c5 2.Nf3 e6 3.d4 cxd4 4.Nxd4 a6 5.Nc3 b5 6.Bd3 Qb6 7.Be3 Bc5 8.Nce2 Nf6 9.O-O Ng4 10.Bd2 e5 11.b4 Bxd4 12.Nxd4 Nxf2 13.Rxf2 Qxd4 14.a4 bxa4 15.Rxa4 Qb6 16.Qh5 O-O 17.b5 d6 18.Ba5 Qb7 19.Rc4 g6 20.Qg5 axb5 21.Rc7 Qa6 22.Bd2 Qa2 23.Re7 Nd7 24.Bxb5 f6 25.Qh4 Rf7 26.Re8+ Nf8 27.Bh6 Be6 28.Rxa8 Qxa8 29.Rxf6 Qa7+ 30.Kf1 Rxf6+ 31.Qxf6 Qf7 32.Qxf7+ Kxf7 33.Bc6 Nd7 34.Bxd7 Bxd7",
                            "1.e4 c5 2.c3 d5 3.exd5 Qxd5 4.d4 Nc6 5.Nf3 Bg4 6.Be2 cxd4 7.cxd4 e6 8.Nc3 Bb4 9.O-O Qa5 10.a3 Bxc3 11.bxc3 Nf6 12.Rb1 O-O 13.Rb5 Qc7 14.h3 Bf5 15.Nh4 Bg6 16.Nxg6 hxg6 17.Bf3 a6 18.Rc5 Nd7 19.Rg5 Ne7 20.Qb3 Rab8 21.g3 Rbc8 22.Qxb7 Qxb7 23.Bxb7 Rxc3 24.Bd2 Rxa3 25.Bb4 Rb3 26.Bxe7 Re8 27.Bxa6 Rxe7 28.Rc1 Nf6 29.Rc8+ Re8 30.Rgc5 Rb8 31.Rxe8+ Rxe8 32.Kg2 Rd8 33.Rc4 Kf8 34.Kf3 Rb8 35.Rc3 Nd5 36.Rc5 Rb4 37.Ke4 Nf6+ 38.Ke3 Rb3+ 39.Ke2 Rb2+ 40.Kf3 Rb4 41.Ke3 Nd5+ 42.Ke4 Nf6+ 43.Ke3 Rb3+ 44.Ke2 Rb2+",
                            "1.d4 d5 2.c4 e6 3.Nf3 Nf6 4.g3 Be7 5.Bg2 O-O 6.O-O dxc4 7.Qc2 a6 8.Qxc4 b5 9.Qc2 Bb7 10.Bf4 Nc6 11.Rd1 Nb4 12.Qc1 Nbd5 13.Nbd2 Nxf4 14.gxf4 c5 15.dxc5 Qc7 16.Nb3 Rac8 17.Ne5 Bxg2 18.Kxg2 Bxc5 19.Nxc5 Qxc5 20.Qxc5 Rxc5 21.Rac1 Rxc1 22.Rxc1 Nd5 23.Nd3 g6 24.Rc6 a5 25.Kf3 Ra8 26.Rc5 b4 27.Rb5 Ra7 28.e4 Nf6 29.Ne5 Rc7 30.Rxa5 Rc2 31.Ra8+ Kg7 32.Ra7 Kg8 33.Ra8+ Kg7 34.Ra7 Kg8 35.Rxf7 Nh5 36.Ra7 Rxb2 37.Nd3 Rc2 38.Ke3 Rc3 39.Kd2 Rc4 40.f3 Rd4 41.Ke3 Rc4 42.Rb7 Rc2 43.Nxb4 Rxh2 44.a4 Rb2 45.a5 Rb3+ 46.Kd4 Nxf4 47.a6 Ra3 48.a7",
                            "1.c4 c5 2.g3 Nc6 3.Bg2 g6 4.Nc3 Bg7 5.a3 d6 6.Rb1 a5 7.Nf3 Nf6 8.O-O O-O 9.Ne1 Bd7 10.Nc2 Rb8 11.d3 Ne8 12.Bd2",
                            "1.e4 c5 2.d4 cxd4 3.c3 Nc6 4.cxd4 d5 5.exd5 Qxd5 6.Nf3 e5 7.Nc3 Bb4 8.Bd2 Bxc3 9.Bxc3 e4 10.Nd2 Nf6 11.Bc4 Qg5 12.Qb3 O-O 13.O-O-O Bg4 14.h4 Bxd1 15.Rxd1 Qf5 16.g4 Nxg4 17.Rg1 Nxf2 18.d5 Ne5 19.Rg5 Qd7 20.Bxe5 f5 21.d6+",
                            "1.e4 Nc6 2.d4 e5 3.d5 Nce7 4.g3 Ng6 5.Bg2 Bc5 6.Ne2 d6 7.c4 f5 8.Nbc3 Nf6 9.b4 Bb6 10.exf5 Bxf5 11.Na4 O-O 12.O-O Bd7 13.Nxb6 axb6 14.Nc3 Qc8 15.Bg5 Bh3 16.Bxf6 Bxg2 17.Kxg2 Rxf6 18.Ne4 Rf8 19.c5 Qf5 20.Qe2 bxc5 21.bxc5 Ra4 22.Rfe1 dxc5 23.Nxc5 Rh4 24.f3 Qh3+ 25.Kg1 Rh6 26.Ne6 Rf7 27.Ng5 Qf5 28.Nxf7 Qxf7 29.Rad1 Rh5 30.Qe4 Qd7 31.d6 cxd6 32.Qd5+ Kh8 33.Qxd6 Qf7 34.Qb8+ Nf8 35.Rd8 Kg8 36.Red1 Qxf3 37.Rxf8+ Qxf8 38.Rd8 Rf5",
                            "1.c4 Nf6 2.Nc3 c5 3.g3 d5 4.cxd5 Nxd5 5.Bg2 Nc7 6.Nf3 Nc6 7.Qa4 Bd7 8.Qe4 g6 9.Ne5 Bg7 10.Nxd7 Qxd7 11.O-O Rc8 12.d3 O-O 13.Be3 Ne6 14.Qa4 Rfd8 15.Rac1 b6 16.Rfd1 Ned4 17.Bxd4 Nxd4 18.Qxd7 Rxd7 19.e3 Nc6 20.d4 Nb4",
                            "1.d4 Nf6 2.c4 e6 3.Nc3 Bb4 4.Qc2 O-O 5.a3 Bxc3+ 6.Qxc3 b6 7.Bg5 Bb7 8.f3 d5 9.e3 Nbd7 10.Bd3 h6 11.Bh4 Qe8 12.Bg3 Rc8 13.c5 bxc5 14.dxc5 d4 15.Qxd4 e5 16.Qc3 e4 17.c6 exd3 18.Bf2 Nd5 19.cxd7 Qxd7 20.Qxd3 Qe6 21.O-O-O c5 22.Qc4 Rfd8 23.e4 Ne3 24.Rxd8+ Rxd8 25.Qe2 Qc4+",
                            "1.d4 Nf6 2.c4 e6 3.Nc3 Bb4 4.Bg5 O-O 5.e3 b6 6.Qf3 Nc6 7.Bd3 Bb7 8.Qh3 h6 9.Bh4 Be7 10.f4 d5 11.cxd5 Nxd5 12.Bxe7 Qxe7 13.Nge2 Ncb4 14.Bb1 c5 15.O-O Nxc3 16.bxc3 Nc6 17.Bd3 cxd4 18.exd4 Na5 19.Rae1 f5 20.g4 fxg4 21.Qxg4 Bd5 22.Qg6 Rf6 23.Qh7+ Kf7 24.f5 Qf8 25.Nf4 Bxa2 26.fxe6+ Ke8 27.e7 Qg8 28.Bb5+",
                            "1.e4 c6 2.d4 d5 3.exd5 cxd5 4.c4 Nf6 5.Nc3 e6 6.Nf3 Bb4 7.Bd3 dxc4 8.Bxc4 O-O 9.O-O Nc6 10.Bg5 a6 11.Bd3 Be7 12.Rc1 b6 13.d5 exd5 14.Bxf6 Bxf6 15.Nxd5 Bb7 16.Be4 Rc8 17.Qb3 b5 18.Rfd1 Na5 19.Rxc8 Bxc8 20.Qc2 g6 21.Qc5 Re8 22.b4 Nc4 23.Ne3 Qb6 24.Nd5 Qd8 25.Qc6 Kg7 26.Ne3 Qe7 27.Nd5",
                            "1.Nf3 Nf6 2.c4 e6 3.g3 d5 4.d4 dxc4 5.Qa4+ c6 6.Qxc4 b5 7.Qc2 Bb7 8.Bg2 Nbd7 9.O-O Qb6 10.Nc3 a6 11.a4 Rc8 12.Bf4",
                            "1.e4 c5 2.Nf3 d6 3.Nc3 Nc6 4.d4 cxd4 5.Nxd4 Nxd4 6.Qxd4 a6 7.Bg5 Qa5 8.f4 e5 9.Qd2 f6 10.Bh4 Be6 11.f5 Bf7 12.Bf2 Ne7 13.b4 Qc7 14.b5 Nc8 15.Rb1 Be7 16.bxa6 bxa6 17.Nd5 Qc6 18.c4 O-O 19.Bd3 Bd8 20.O-O Bxd5 21.cxd5 Qa4 22.Rb7 Na7 23.Rxa7 Ba5",
                            "1.e4 c5 2.Nf3 d6 3.d4 cxd4 4.Nxd4 Nf6 5.Nc3 Nc6 6.Bg5 e6 7.Qd2 a6 8.O-O-O h6 9.Nxc6 bxc6 10.Bf4 d5 11.Qe3 Be7 12.Be2 Qa5 13.exd5 Nxd5 14.Nxd5 cxd5 15.Be5 O-O 16.Kb1 Bd7 17.Qg3 f6 18.Bf4 Kh7 19.c4 Bc6 20.Bd3+ f5 21.Rhe1 Bf6 22.c5 Qb4 23.Bc1 Ba4 24.Rd2 Rac8 25.Rxe6 Bg5 26.f4 Qxf4 27.Qxf4 Bxf4 28.Rf2 Bxc1 29.Rxf5 Rxf5 30.Bxf5+ Kg8 31.Rxa6 Rxc5 32.Rxa4 Bg5 33.b4 Rc1+ 34.Kb2 Re1 35.Bg6 Re2+ 36.Kc3",
                            "1.d4 Nf6 2.Nf3 d5 3.c4 e6 4.Nc3 Be7 5.Bg5 h6 6.Bxf6 Bxf6 7.cxd5 exd5 8.b4 O-O 9.e3 c6 10.h3 Be6 11.Bd3 Nd7 12.O-O b5 13.a4 a6 14.a5 c5 15.bxc5 Nxc5 16.Bc2 Rc8 17.dxc5 Rxc5 18.Qd3 g6 19.Nd4 Bf5 20.Nxf5 Rxc3 21.Nxh6+ Kh7 22.Nxf7 Rxd3 23.Nxd8 Rd2 24.Ne6 Rc8 25.Bb3 Bxa1 26.Rxa1 Rc3 27.Rb1 Rc4 28.Nd4",
                            "1.Nf3 Nf6 2.d4 e6 3.c4 d5 4.Nc3 dxc4 5.e4 Bb4 6.Bg5 c5 7.Bxc4 cxd4 8.Nxd4 Qa5 9.Bb5+ Bd7 10.Bd2 Bxb5 11.Ndxb5 Nxe4 12.Qg4 Nxd2 13.Qxg7 Rf8 14.O-O-O a6 15.Qe5 axb5 16.Nd5 Nd7 17.Qg5 Rc8+",
                            "1.e4 c5 2.Nc3 e6 3.Nf3 d5 4.exd5 exd5 5.Bb5+ Nc6 6.O-O Bd6 7.Nxd5 Bxh2+ 8.Kxh2 Qxd5 9.d4 Nf6 10.Kg1 O-O 11.c4 Qh5 12.d5 Ne5 13.Nxe5 Qxe5 14.Re1 Qd6 15.Qf3 a6 16.Bf4 Qd8 17.Ba4 Ng4 18.Qg3 b5 19.cxb5 axb5 20.Bxb5 Qxd5 21.Bd6 Rd8 22.Be7 Rd7 23.Bxd7 Bxd7 24.Rad1 Qf5 25.Qf3 Re8 26.Bxc5 Rxe1+ 27.Rxe1 Qxc5 28.Qa8+ Qf8 29.Qxf8+ Kxf8 30.b4 f6 31.f4 Bb5 32.Rc1 Kf7 33.Rc5 Bd3 34.b5",
                            "1.d4 e6 2.c4 f5 3.Nc3 Nf6 4.h3 Bb4 5.g4 Ne4 6.Qd3 b6 7.Nf3 Bb7 8.gxf5 exf5 9.Rg1 Qe7 10.Bf4 d6 11.Ng5 Bxc3+ 12.bxc3 h6 13.Nf3 g5 14.Be3 f4 15.Bc1 Nd7 16.h4 O-O-O 17.Bh3 Kb8 18.Ba3 gxh4 19.d5 Ng5 20.Bxd7 Qxd7 21.Nxh4 Qa4 22.Bc1 Ba6 23.Rg4",
                            "1.d4 Nf6 2.c4 e6 3.g3 d5 4.Bg2 dxc4 5.Qa4+ Bd7 6.Qxc4 Bc6 7.Bxc6+ Nxc6 8.Nf3 Qd5 9.Qxd5 exd5 10.O-O Ne4 11.Bf4 O-O-O 12.Rd1 Be7 13.Ne5 Nxe5 14.Bxe5 f6 15.Bf4 g5 16.Be3 Nd6 17.Nc3 Nc4 18.Bc1 Bb4 19.Rd3 Bxc3 20.Rxc3 Rde8 21.b3 Nd6 22.Kf1 h5 23.a4 Nf5 24.Bb2 g4 25.Rac1 c6 26.f3 h4 27.e4 hxg3 28.hxg3 Nxd4 29.fxg4 Rxe4 30.Rd3 Rh1+ 31.Kg2 Rxc1 32.Bxc1 Rxg4 33.Be3 c5 34.Bxd4 Rxd4 35.Rxd4 cxd4 36.Kf2 Kd7 37.Ke2 Kd6 38.b4 Ke5 39.Kd3 f5",
                            "1.Nf3 Nf6 2.g3 g6 3.Bg2 Bg7 4.O-O O-O 5.c4 d6 6.d4 Nbd7 7.Nc3 e5 8.e4 a6 9.Re1 exd4 10.Nxd4 Re8 11.f3 Rb8 12.Nde2 Ne5 13.b3 c5 14.a4 Nc6 15.Be3 Nb4 16.Qd2 Be6 17.Rad1 Qb6 18.Bf2 Rbd8 19.Nf4 Bc8 20.Rb1 Qc7 21.g4 g5 22.Nfd5 Nbxd5 23.Nxd5 Nxd5 24.cxd5 h6 25.a5 Bd7 26.h4 gxh4 27.Bxh4 Rb8 28.g5 hxg5 29.Qxg5 c4 30.f4 c3 31.Re3 Qc5 32.Bf2 c2 33.Rc1 f6 34.Qxg7+ Kxg7 35.Rg3+ Kf7 36.Bxc5 dxc5 37.Rxc2 b6 38.axb6 Rec8 39.e5 fxe5 40.fxe5 Rxb6",
                            "1.e4 e5 2.Nf3 Nc6 3.Bb5 a6 4.Ba4 Nf6 5.O-O b5 6.Bb3 Bc5 7.c3 Nxe4 8.Qe2 d5 9.d3 Nf6 10.d4 Bb6 11.dxe5 Ne4 12.Be3 Bxe3 13.Qxe3 O-O 14.Rd1 Be6 15.Nd4 Nxe5 16.f3 Nc4 17.Bxc4 dxc4 18.fxe4 c5 19.Nd2 cxd4 20.cxd4 Qb6 21.Nf1 Rae8 22.d5 Qxe3+ 23.Nxe3 Bd7 24.Rd4 Re5 25.a4 f5 26.Nxf5 Bxf5 27.exf5 Re2 28.axb5 axb5 29.Rb1 Rxf5 30.d6 Rff2 31.d7",
                            "1.d4 Nf6 2.c4 c6 3.Nc3 d5 4.Nf3 e6 5.cxd5 exd5 6.Bg5 Be7 7.Qc2 g6 8.e3 Bf5 9.Bd3 Bxd3 10.Qxd3 O-O 11.Bxf6 Bxf6 12.O-O a5 13.Rad1 Na6 14.Rfe1 Bg7 15.h3 f5 16.a3 Qd6 17.Na4 Nc7 18.Nc5 b6 19.Na4 c5 20.dxc5 bxc5 21.Qc2 Ne6 22.Nc3 Bxc3 23.bxc3 c4 24.Rd2 Nc5 25.Red1 Ne4 26.Rxd5 Qxa3 27.Rc1 Rab8 28.Rd7 Nxf2 29.Qxf2 Qxc1+ 30.Kh2 Rfd8 31.Rxd8+ Rxd8 32.Qh4 Qd1 33.Nd4 Re8 34.Qf6 Qd3 35.Qc6 Qxe3 36.Qxc4+ Kg7 37.Qc7+ Re7",
                            "1.e4 e5 2.Nf3 Nc6 3.Nc3 Nf6 4.a3 g6 5.Nxe5 Nxe5 6.d4 Nc6 7.d5 Nb8 8.e5 Ng8 9.d6 cxd6 10.exd6 Qf6 11.Nb5 Na6 12.Bc4 Bh6 13.Qe2+ Kf8 14.Be3 Bxe3 15.fxe3 Qh4+ 16.g3 Qh5 17.Qf2 Qf5 18.Qe2 Qh5 19.Qf2 Qf5 20.Qe2 Nh6 21.Rf1 Qh5 22.Qf2 Qf5 23.Qe2 Qe5 24.O-O-O Kg7 25.Rd5 Qe8 26.Qd2 Rf8 27.Qd4+ f6 28.g4 b6 29.g5 Nf5 30.gxf6+ Rxf6 31.Rdxf5 gxf5 32.Rg1+ Qg6 33.Rxg6+ Kxg6 34.Bd5 Rb8 35.e4 Bb7 36.exf5+ Rxf5 37.Qg4+ Kf6 38.Qh4+ Kg6 39.Bc4 Nc5 40.b4 Ne4 41.Nc7 Nxd6 42.Qg3+",
                            "1.e4 c6 2.d4 d5 3.exd5 cxd5 4.c4 Nf6 5.Nc3 e6 6.Nf3 Bb4 7.Bd3 dxc4 8.Bxc4 O-O 9.O-O b6 10.Bg5 Bb7 11.Qb3 Be7 12.Ne5 Nfd7 13.Nxf7 Rxf7 14.Bxe6 Bxg5 15.Bxf7+ Kh8 16.Bd5 Nc6 17.Qa4 Rc8 18.Be6 a6 19.Ne4 Be7 20.d5 Nce5 21.d6 Bf8 22.f4 b5 23.Qd4 Nc6 24.Qe3 h6 25.Ng5 Qe8 26.Nf7+ Kh7 27.Qe4+ g6 28.f5 Nd8 29.fxg6+ Kg7 30.Qd4+ Kxg6 31.Qg4+",
                            "1.e4 c5 2.Nf3 d6 3.d4 Nf6 4.Nc3 cxd4 5.Nxd4 Nc6 6.Bg5 e6 7.Qd2 a6 8.Be2 Bd7 9.Rd1 b5 10.a3 Rc8 11.O-O h6 12.Be3 Be7 13.f4 O-O 14.Nb3 Re8 15.Bf3 e5 16.Nd5 Nxd5 17.exd5 exf4 18.Bxf4 Ne5 19.Bxe5 dxe5 20.Be4 Bd6 21.Qd3 Rf8 22.Rd2 a5 23.Bf5 Bxf5 24.Qxf5 g6 25.Qf6 a4 26.Nc1 Bc5+ 27.Kh1 Qxf6 28.Rxf6 Be3 29.Rd1 Rxc2 30.Nd3 e4 31.Nb4 Rxb2 32.d6 Rd2 33.Re1 Bc5 34.Rff1 Bxb4 35.axb4 Re8 36.g4 Rxd6 37.Rd1 Rxd1 38.Rxd1 e3 39.Kg2 Re4",
                            "1.e4 c5 2.Nf3 d6 3.d4 cxd4 4.Nxd4 Nf6 5.Nc3 g6 6.Be3 Bg7 7.f3 Nc6 8.Qd2 O-O 9.O-O-O d5 10.exd5 Nxd5 11.Nxc6 bxc6 12.Nxd5 cxd5 13.Qxd5 Qc7 14.Qc5 Qb8 15.Qa3 a5 16.Bd4 Rd8 17.Qc5 Bf5 18.Bc4 Rc8 19.Qd5 e6 20.Qxa8 Qxa8 21.Bxg7 Kxg7 22.Bd3",
                            "1.e4 e6 2.d4 d5 3.exd5 exd5 4.Nf3 Nf6 5.c4 Bb4+ 6.Nc3 O-O 7.Be3 Nc6 8.Bd3 dxc4 9.Bxc4 Bg4 10.O-O Qd6 11.a3 Bxc3 12.bxc3 Na5 13.Bd3 Qd5 14.Rb1 a6 15.h3 Bh5 16.g4 Bg6 17.Ne5 Bxd3 18.Qxd3 b5 19.Rfe1 Nc4 20.Bg5 Nd7 21.Nxc4 bxc4 22.Qe3 Nb6 23.Bf4 Qd7 24.Qg3 Nd5 25.Re5 f6 26.Re2 Rab8 27.Reb2 Rxb2 28.Rxb2 Qe7 29.Rb1 Qe4",
                            "1.Nf3 Nf6 2.g3 d5 3.Bg2 e6 4.O-O Be7 5.c4 O-O 6.d4 c6 7.Qc2 Nbd7 8.b3 b6 9.Bb2 Bb7 10.Nbd2 Rc8 11.e4 c5 12.exd5 exd5 13.Qf5 dxc4 14.Nxc4 Be4 15.Qh3 Re8 16.Rad1 Qc7 17.dxc5 Bxc5 18.Nd4 Bxg2 19.Qxg2 Bxd4 20.Bxd4 Re2 21.a4 Qc6 22.Qxc6 Rxc6 23.Ne3 a6 24.Bxf6",
                            "1.d4 Nf6 2.c4 e6 3.Nf3 b6 4.Nc3 Bb7 5.a3 d5 6.cxd5 Nxd5 7.Qc2 Be7 8.e4 Nxc3 9.bxc3 c5 10.Bb5+ Bc6 11.Bd3 O-O 12.O-O cxd4 13.cxd4 Bb7 14.Bf4 Nc6 15.d5 exd5 16.exd5 Qxd5 17.Bxh7+ Kh8 18.Be4 Qc5 19.Qe2 f5 20.Bxc6 Bxc6 21.Ne5 Be8 22.Nd3 Qd5 23.Qxe7 Bc6 24.Qh4+ Kg8 25.Qg3",
                            "1.d4 Nf6 2.c4 e6 3.Nf3 d5 4.Nc3 Bb4 5.Bg5 h6 6.Bxf6 Qxf6 7.Qb3 Bxc3+ 8.Qxc3 c6 9.e3 Nd7 10.Bd3 dxc4 11.Bxc4 O-O 12.Bd3 c5 13.O-O b6 14.Be4 Rb8 15.b4 Bb7 16.Bxb7 Rxb7 17.Rac1 Rc8 18.dxc5 bxc5 19.Qxf6 gxf6 20.a3 Rcc7 21.g3 cxb4 22.Rxc7 Rxc7 23.axb4 Rb7 24.Ra1 Rxb4 25.Rxa7 Nc5 26.Ra2 Kg7 27.Kg2 Rb7 28.Rc2 Ne4 29.Nd4 f5 30.Ne2 Rd7 31.Nd4 Rb7 32.h3 Rd7 33.Kf3 Ng5+ 34.Kg2 Ne4",
                            "1.g3 d5 2.Nf3 c6 3.Bg2 Bf5 4.O-O Nd7 5.d3 h6 6.Re1 Ngf6 7.Nc3 e5 8.e4 dxe4 9.Nxe4 Nxe4 10.dxe4 Be6 11.Qe2 Bc5 12.a3 O-O 13.b4 Bb6 14.Bb2 Qf6 15.c4 Bc7 16.c5 a5 17.Nd2 axb4 18.axb4 b6 19.cxb6 Bxb6 20.Nf3 Qe7 21.Nxe5 Nxe5 22.Bxe5 Qxb4 23.Rab1 Qc5 24.Rec1 Qxe5 25.Rxb6 c5 26.Rb5 Rfc8 27.h3 Ra1 28.Qe1 Rxc1 29.Qxc1 Qd4 30.Rb2 c4 31.Rd2 Qe5 32.f4 Qc5+ 33.Kh2 c3 34.Rd3 c2 35.f5 Ba2 36.Rd7 Qb5 37.Ra7 Qb1",
                            "1.e4 e5 2.Nf3 Nc6 3.Bb5 Nf6 4.d3 Bc5 5.c3 O-O 6.O-O d6 7.h3 a6 8.Bxc6 bxc6 9.Re1 Bb6 10.Nbd2 a5 11.Nc4 h6 12.d4 exd4 13.cxd4 Re8 14.Qc2 c5 15.d5 a4 16.Bd2 Bd7 17.Bc3 Bb5 18.b3 Nd7 19.Nfd2 Qe7 20.Re3 c6 21.Rg3 f6 22.Ne3 Qf8 23.Nf5 g5 24.dxc6 Bxc6 25.Rd1 Ne5 26.Bxe5 Rxe5 27.Re3 Bc7 28.Nc4 Re6 29.Qe2 axb3 30.axb3 Kh7 31.Qh5 Be8 32.Qg4 Qf7 33.Nfxd6 Bxd6 34.Nxd6 Qe7 35.e5 fxe5 36.Qe4+",
                            "1.e4 e5 2.Nf3 Nc6 3.Bb5 Nf6 4.d3 Bc5 5.Bxc6 dxc6 6.Nbd2 Be6 7.O-O Nd7 8.Nb3 Bb6 9.Ng5 Bxb3 10.axb3 Qe7 11.Bd2 O-O-O 12.b4 Kb8 13.c4 Bd4 14.Nf3 Nf8 15.Qa4 a6 16.b5 cxb5 17.cxb5 Qd7 18.bxa6 Qxa4 19.Rxa4 Ne6 20.axb7 Nc5 21.Ra3 Bxb2 22.Ra2 Nxd3 23.Rb1 c5",
                            "1.e4 e5 2.Nf3 Nc6 3.Bb5 a6 4.Ba4 Nf6 5.d3 b5 6.Bb3 Bc5 7.Nc3 d6 8.Nd5 h6 9.c3 O-O 10.O-O Rb8 11.Re1 Ba7 12.Be3 Bxe3 13.Rxe3 Na5 14.Bc2 c5 15.b4 cxb4 16.Nxb4 Qc7 17.Qd2 Nc6 18.Nxc6 Qxc6 19.h3 Be6 20.d4 Qc7 21.Bb3 Rfe8 22.Bxe6 Rxe6 23.a4 exd4 24.Qxd4 bxa4 25.Qxa4 Rbe8 26.Qxa6 Rxe4 27.Rxe4 Rxe4 28.Qd3 Re8 29.Nd4 d5 30.Nf5 Qf4 31.g3 Qe4 32.Rd1 Qxd3 33.Rxd3 Kf8 34.f3 Ra8 35.g4 Ra3 36.Kf2 h5 37.Ke3 g6 38.Nd4 hxg4 39.hxg4 Nd7 40.Nb5 Rb3 41.Rxd5 Nb6 42.Rc5 Na4 43.Rc8+ Kg7 44.Rc4 Nb6 45.Rc5 Na4 46.Rc4 Nb6 47.Rc5 Na4 48.Rc4"};

    vector<int> chess_winners = {0, 1, 0, 2, 1, 1, 1, 2, 2, 2, 2, 2, 0, 1, 1,
                                 0, 1, 0, 0, 1, 0, 1, 1, 0, 2, 1, 0, 0, 1, 1,
                                 1, 2, 1, 0, 2, 1, 0, 2, 1, 1, 2, 2, 2, 1, 1,
                                 0, 2, 1, 1, 0};

    vector<string> checkers = {"1. 20-16 21-17 2. 18-22 26-23 3. 22-26 23-18 4. 26-30 17-13 5. 30-26 18-14 6. 26-22 14-9 7. 22-17 9-5 8. 16-11 5-1 9. 17-14 1-6 10. 11-15 6-1 11. 15-10",
                               "1. 4-8 27-23 2. 11-16 29-25 3. 16-20 25-21 4. 20-24 23-18 5. 24-27 18-14 6. 27-31 21-17 7. 31-26 17-13 8. 26-22",
                               "1. 5-9 10-6 2. 9-14 6-2 3. 14-18 2-6 4. 18-23 29-25 5. 13-17 6-9 6. 23-27 9-13 7. 17-14 25-21 8. 27-31 13-17 9. 14-9 17-13 10. 9-5 13-17 11. 31-27 17-14 12. 27-23 21-17 13. 23-19 14-18 14. 5-9 17-13 15. 9-5 18-14 16. 19-15",
                               "1. 31-26 3-7 2. 26-22 2-6 3. 22-17 7-10 4. 15-11 10-15 5. 11-7 15-10 6. 7-3",
                               "1. 30-26 32-28 2. 24-27 28-24 3. 26-23 4-8 4. 27-32 8-12 5. 23-18 24-19 6. 32-27 12-8 7. 27-24 19-16 8. 24-19 16-11 9. 18-14 11-7 10. 14-10 7-3 11. 19-16",
                               "1. 16-11 21-17 2. 32-28 25-22 3. 11-7 17-14 4. 28-24 22-18 5. 24-19 18-23 6. 19-15",
                               "1. 2-7 10-15 2. 7-2 15-18 3. 2-6 18-14 4. 6-2 14-9 5. 25-22 9-14 6. 2-6 3-8 7. 6-2 8-12 8. 2-7 12-16 9. 7-1",
                               "1. 30-26 32-28 2. 24-27 28-24 3. 26-23 4-8 4. 27-32 24-20 5. 23-19 8-12 6. 32-27 20-16 7. 27-23 16-11 8. 19-15 11-7 9. 23-19 12-8 10. 19-16",
                               "1. 30-26 32-28 2. 24-27 28-24 3. 26-23 4-8 4. 27-32 8-12 5. 23-18 24-19 6. 32-27 12-8 7. 27-24 19-16 8. 24-19 16-11 9. 18-14 11-7 10. 14-10 7-3 11. 19-16",
                               "1. 2-6 32-28 2. 6-10 28-24 3. 23-27 24-19 4. 27-31 19-16 5. 31-27 16-11 6. 27-23 11-7 7. 10-15 7-2 8. 15-19 2-6 9. 23-18 6-9 10. 18-22 9-14 11. 19-24 14-10 12. 24-27 10-15 13. 27-32 15-10 14. 32-27 10-6 15. 27-23 6-1 16. 23-18 1-6 17. 18-14 6-1 18. 22-18 1-6 19. 18-15 6-1 20. 15-10 1-5 21. 10-6 5-1 22. 14-10 1-5 23. 6-1 5-9 24. 1-5 9-13 25. 10-14 13-9 26. 14-18 9-6 27. 18-15 30-25 28. 15-18 6-10 29. 5-1 25-21 30. 1-5 10-6 31. 18-15 21-17 32. 5-1 6-9 33. 15-18 17-13 34. 18-15 9-14 35. 1-5 14-17 36. 15-10 17-22 37. 10-14 22-25 38. 5-1 25-22 39. 1-6 22-25 40. 6-10 25-22 41. 10-15 22-25 42. 15-18 25-21 43. 18-22"};

    vector<int> checkers_winners = {1, 1, 1, 0, 1, 0, 0, 1, 1, 1};

    vector<string> days = {"01", "02", "03", "04", "05", "06", "07", "08",
                           "09", "10", "11", "12", "13", "14", "15", "16",
                           "17", "18", "19", "20", "21", "22", "23", "24",
                           "25", "26", "27", "28"};

    vector<string> months = {"01", "02", "03", "04", "05", "06", "07", "08",
                             "09", "10", "11", "12"};

    vector<int> years = {2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017,
                         2018, 2019, 2020, 2021};

    int i = 0;
    // Generate chess games.
    for (; i < NUMBER_OF_CHESS_GAMES; ++i) {
        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<mt19937::result_type> dist10(0,9);
        uniform_int_distribution<mt19937::result_type> dist12(0,11);
        uniform_int_distribution<mt19937::result_type> dist28(0,27);
        uniform_int_distribution<mt19937::result_type> dist50(0,49);

        int player1, player2, day, month, year, moves;

        player1 = player2 = dist50(rng);
        while (player2 == player1)
            player2 = dist50(rng);

        day = dist28(rng);
        month = dist12(rng);
        year = dist12(rng);
        moves = dist50(rng);

        cout << "insert into Record values (" << i << ", " << "DATE '"
             << years[year] << "-" << months[month] << "-" << days[day]
             << "', '" << chess[moves] << "', " << 0 << ", '" << nicks[player1]
             << "', '" << nicks[player2] << "', " << chess_winners[moves]
             << ");\n";
    }

    // Generate checkers games.
    for (; i < NUMBER_OF_CHESS_GAMES + NUMBER_OF_CHECKERS_GAMES; ++i) {
        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<mt19937::result_type> dist10(0,9);
        uniform_int_distribution<mt19937::result_type> dist12(0,11);
        uniform_int_distribution<mt19937::result_type> dist28(0,27);
        uniform_int_distribution<mt19937::result_type> dist50(0,49);

        int player1, player2, day, month, year, moves;

        player1 = player2 = dist50(rng);
        while (player2 == player1)
            player2 = dist50(rng);

        day = dist28(rng);
        month = dist12(rng);
        year = dist12(rng);
        moves = dist10(rng);

        cout << "insert into Record values (" << i << ", " << "DATE '"
             << years[year] << "-" << months[month] << "-" << days[day]
             << "', '" << checkers[moves] << "', " << 1 << ", '"
             << nicks[player1] << "', '" << nicks[player2] << "', "
             << checkers_winners[moves] << ");\n";
    }

    return 0;
}
