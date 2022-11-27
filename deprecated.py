def find_T():
    global Ts,free_str,T_a,T_b
    T_a = np.zeros((N*2,N*2),dtype="float64")
    T_b = np.zeros((N*2,),dtype="float64")
    Fs = np.zeros((N,2),dtype="float64")
    last_i = -1
    for i in range(0,N*2,2):
        T_a[i,last_i+1] = m 
        if free_str[i//2][0]:
            T_a[i+1,last_i+2] = m
            last_i += 2
        else:
            T_a[i+1,last_i+1] = m
            last_i += 1
    for i in range(N):
        Fs[i,0] = xv1_eq(i,oo=True)*m
        Fs[i,1] = yv1_eq(i,oo=True)*m
    for i in range(0,N*2,2):
        d1 = dist(i//2,(i//2+1)%N)
        xn1 = (xs[(i//2+1)%N]-xs[i//2])/d1
        yn1 = (ys[(i//2+1)%N]-ys[i//2])/d1
        d2 = dist(i//2,(i//2-1)%N)
        xn2 = (xs[(i//2-1)%N]-xs[i//2])/d2
        yn2 = (ys[(i//2-1)%N]-ys[i//2])/d2
        T_b[i] = (Fs[i//2,0]*xn1+Fs[i//2,1]*yn1)
        T_b[(i-1)%(2*N)] = -(Fs[i//2,0]*xn2+Fs[i//2,1]*yn2)
        if not free_str[i//2][0]:
            T_a[i,last_i+1+free_str[i//2][1]] = -1
            T_a[(i-1)%(2*N),last_i+1+free_str[i//2][1]] = (xn1*xn2+yn1*yn2)
        else:
            T_b[i] += k*(d1-l0)
            T_b[(i-1)%(2*N)] -= k*(d1-l0)*(xn1*xn2+yn1*yn2)
        if not free_str[(i//2-1)%N][0]:
            T_a[i,last_i+1+free_str[(i//2-1)%N][1]] = -(xn1*xn2+yn1*yn2)
            T_a[(i-1)%(2*N),last_i+1+free_str[(i//2-1)%N][1]] = 1
        else:
            T_b[i] += k*(d2-l0)*(xn1*xn2+yn1*yn2)
            T_b[(i-1)%(2*N)] -= k*(d2-l0)
    Ts = np.linalg.solve(T_a,T_b)[last_i+1:]


def strings():
    stretched_strs = []
    i_in_table = dict()
    for i,fr in enumerate(free_str):
        d = dist(i,(i+1)%N)
        xn = (xs[(i+1)%N]-xs[i])/d
        yn = (ys[(i+1)%N]-ys[i])/d
        v = xvs[i]*xn+yvs[i]*yn
        vn = xvs[(i+1)%N]*xn+yvs[(i+1)%N]*yn
        vr = v - vn
        if not fr[0] and vr < 0:
            stretched_strs.append((i,(i+1)%N))
            if not i in i_in_table:
                i_in_table[i] = len(i_in_table)
            if not (i+1)%N in i_in_table:
                i_in_table[(i+1)%N] = len(i_in_table)
    dim = 2*len(i_in_table)
    dv_A = np.zeros((dim,dim))
    dv_B = np.zeros((dim,))
    for st_str in stretched_strs:
        d = dist(st_str[0],st_str[1])
        xn = (xs[st_str[1]]-xs[st_str[0]])/d
        yn = (ys[st_str[1]]-ys[st_str[0]])/d

        dv_A[i_in_table[st_str[0]],i_in_table[st_str[0]]] += xn**2
        dv_A[i_in_table[st_str[0]],i_in_table[st_str[1]]] -= xn**2
        dv_A[i_in_table[st_str[0]],i_in_table[st_str[1]]+dim//2] -= xn*yn

        dv_A[i_in_table[st_str[0]]+dim//2,i_in_table[st_str[0]]+dim//2] += yn**2
        dv_A[i_in_table[st_str[0]]+dim//2,i_in_table[st_str[1]]+dim//2] -= yn**2
        dv_A[i_in_table[st_str[0]]+dim//2,i_in_table[st_str[1]]] -= xn*yn

        dv_A[i_in_table[st_str[1]],i_in_table[st_str[1]]] += xn**2
        dv_A[i_in_table[st_str[1]],i_in_table[st_str[0]]] -= xn**2
        dv_A[i_in_table[st_str[1]],i_in_table[st_str[0]]+dim//2] -= xn*yn

        dv_A[i_in_table[st_str[1]]+dim//2,i_in_table[st_str[1]]+dim//2] += yn**2
        dv_A[i_in_table[st_str[1]]+dim//2,i_in_table[st_str[0]]+dim//2] -= yn**2
        dv_A[i_in_table[st_str[1]]+dim//2,i_in_table[st_str[0]]] -= xn*yn

        dv_B[i_in_table[st_str[0]]] -= xn*(xvs[st_str[0]]*xn+yvs[st_str[0]]*yn - (xvs[st_str[1]]*xn+yvs[st_str[1]]*yn))
        dv_B[i_in_table[st_str[0]]+dim//2] -= yn*(xvs[st_str[0]]*xn+yvs[st_str[0]]*yn - (xvs[st_str[1]]*xn+yvs[st_str[1]]*yn))
        dv_B[i_in_table[st_str[1]]] -= xn*(xvs[st_str[1]]*xn+yvs[st_str[1]]*yn - (xvs[st_str[0]]*xn+yvs[st_str[0]]*yn))
        dv_B[i_in_table[st_str[1]]+dim//2] -= yn*(xvs[st_str[1]]*xn+yvs[st_str[1]]*yn - (xvs[st_str[0]]*xn+yvs[st_str[0]]*yn))
    for i in i_in_table:
        dv_A[i_in_table[i],i_in_table[i]] += REGULARIZATION_COEF*2
        dv_A[i_in_table[i]+dim//2,i_in_table[i]+dim//2] += REGULARIZATION_COEF*2
    inv_A = np.linalg.pinv(dv_A)
    dvs = inv_A@dv_B
    for i in i_in_table:
        xvs[i] += dvs[i_in_table[i]]
        yvs[i] += dvs[i_in_table[i]+dim//2]