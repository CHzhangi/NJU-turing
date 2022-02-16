#Q = {q0,q1,q2,q3,q4,q5,q6,q7,q8,q9,q_accept_delete0,q_accept}

#S = {0,1}

#G = {0,1,_}

#q0 = q0

#B = _

#N = 2

#F = {q_accept}

;q0 is initial state
;q_accept is terminal state q_accept_delete0 is for delete needless 0 in first tape
q0 0_ 0_ ** q_accept_delete0
q_accept_delete0 0_ __ r* q_accept_delete0
q_accept_delete0 1_ 1_ ** q_accept

;first number 1->0
;record this 1 in second tape
q0 1_ _1 rr q1

;q1 if for finding the 0 in-between
q1 1_ 1_ r* q1
q1 0_ 0_ r* q2

;q2 if for finding second number'1
q2 0_ 0_ r* q2
q2 1_ 0_ r* q3

;need judge the seconde number has been reduced to 0
;ture:q4
;flase q5 
q3 __ __ *l q4
q3 1_ 1_ l* q5

;return to q0
q5 0_ 0_ l* q5
q5 1_ 1_ l* q6
q5 __ __ rl q4
q6 1_ 1_ l* q6
q6 __ __ r* q0
q5 __ __ r* q0

;q4 is for Copy the numbers on tape 2 to tape 1
q4 01 1_ rl q4
q4 _1 1_ rl q4
q4 0_ 0_ l* q9
q4 1_ 1_ l* q9
q4 __ __ l* q9
q9 1_ 1_ l* q9
q9 0_ 0_ l* q9

;keep go on in q0
q9 __ __ r* q0






















