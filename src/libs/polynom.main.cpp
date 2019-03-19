/*
ProCalc — powerful multifunctional calculator
Copyright © 2019 Tushino Software LLC

This file is part of ProCalc.

ProCalc is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

ProCalc is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ProCalc. If not, see <https://www.gnu.org/licenses/>.
*/

#include "../headers/header.h"

int polynom_menu()
{
    double P[MAX_DEG] = {0},
            Q[MAX_DEG] = {0},
            R[MAX_DEG] = {0};
    int P_deg, Q_deg, R_deg = 0;
    double coef = 0.0;

    int func, junk, n;

    while (1) {
        printf(" ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n"
               "|                                                            |\n"
               "|                >> Polynomials calculator <<                |\n"
               "|                                                            |\n"
               "|  >> Choose a function:                                     |\n"
               "|                                                            |\n"
               "|       1) Long division of polynoms                         |\n"
               "|       2) Addition of polynoms                              |\n"
               "|       3) Substraction of polynoms                          |\n"
               "|       4) Multiply polynoms                                 |\n"
               "|       5) Multiply polynom by number                        |\n"
               "|       6) Found deriative of polynom                        |\n"
               "|                                                            |\n"
               "|       >> Type \"back\" to go to the previous menu <<         |\n"
               "|       >> Type \"quit\" to terminate this program <<          |\n"
               "|                                                            |\n");
        printf("| Answer: ");
        func = getchar();
        prt_ln();
        if (isdigit(func) && func >= '1' && func <= '6') {
            func -= '0';
            if ((junk = getchar()) != '\n') {
                while ((junk = getchar()) != '\n')
                    ;
                no_cmd();
                continue;
            }

            switch (1) {
                case 1: {
                        double remain[MAX_DEG] = {0},
                               new_part[MAX_DEG] = {0},
                               multiplier[MAX_DEG] = {0};

                        double P[MAX_DEG] = {-11, 2, 0, 4},
                               Q[MAX_DEG] = {5, 1};
    //                    P_deg = get_p(P);
    //                    Q_deg = get_p(Q);
                        P_deg = 3;
                        Q_deg = 1;
                        // remain = P;
                        copy_p(remain, P);

                        for (int i = P_deg; i >= Q_deg; i--) {
                            R[i - Q_deg] = multiplier[i - Q_deg] = P[i] / Q[Q_deg];
                            mult_p(multiplier, i - Q_deg, Q, Q_deg, new_part);
                            substr_this(P, P_deg, new_part, MAX_DEG-1);

                            if ( i == Q_deg )
                                copy_p(remain, P);

                            zero_p(multiplier);
                            zero_p(new_part);

                        }


                        cout << "\n======== RESULT: ========\n" <<
                                "=== Division result:  ===\n";
                        show_p( R, P_deg - Q_deg );
                        cout << "====== Remainder:  ======\n";
                        show_p( remain, 10 ); // deg - ???

                }
                break;

                case 2:
                    P_deg = get_p( P );
                    Q_deg = get_p( Q );
                    R_deg = (P_deg > Q_deg) ? P_deg : Q_deg;
                    add_p( P, P_deg, Q, Q_deg, R );
                    cout << "\n=== RESULT: ===\n";
                    show_p( R, R_deg );
                    break;
                case 3:
                    P_deg = get_p( P );
                    Q_deg = get_p( Q );
                    R_deg = (P_deg > Q_deg) ? P_deg : Q_deg;
                    substr_p( P, P_deg, Q, Q_deg, R );
                    cout << "\n=== RESULT: ===\n";
                    show_p( R, R_deg );
                    break;
                case 4:
                    P_deg = get_p( P );
                    Q_deg = get_p( Q );
                    R_deg = P_deg * Q_deg;
                    mult_p( P, P_deg, Q, Q_deg, R );
                    cout << "\n=== RESULT: ===\n";
                    show_p( R, R_deg );
                    break;
                case 5:
                    P_deg = get_p( P );
                    cout << "Insert multiplier\n";
                    cin >> coef;
                    R_deg = P_deg;
                    mult_number(P, P_deg, R, coef);
                    cout << "\n=== RESULT: ===\n";
                    show_p( R, R_deg );
                    break;
                case 6:
                    P_deg = get_p( P );
                    R_deg = P_deg - 1;
                    derivative_p(P, P_deg, R, R_deg);
                    cout << "\n=== RESULT: ===\n";
                    show_p( R, R_deg );
                    break;
                default:
                    break;
            }

            zero_p( P );
            zero_p( Q );


            if (!n) {
                func = 'b';
            }

        } else if (func == 'q') {
            if (quit_m()) {
                return -1;
            } else {
                continue;
            }
        } else if (func == 'b') {
            if (back_m()) {
                return 0;
            } else {
                continue;
            }
        } else {
            no_cmd();
            while ((junk = getchar()) != '\n')
                ;
            continue;
        }
    }
}
