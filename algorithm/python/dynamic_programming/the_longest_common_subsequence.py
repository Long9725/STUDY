# def max(a, b):
#     if a < b return b
#     else return a

def LCS(X, Y, m, n):
    b = [[0]*n for _ in range(m)]
    c = [[0]*(n+1) for _ in range(m+1)]
    output = ""

    for i in range(1, m+1):
        for j in range(1, n+1):
            if (X[i-1] == Y[j-1]) :
                c[i][j] = c[i-1][j-1] + 1
                b[i-1][j-1] = 2
            else :
                c[i][j] = max(c[i-1][j], c[i][j-1])
                if c[i][j] == c[i-1][j] and c[i][j] == c[i][j-1]:
                    b[i-1][j-1] = 4 # 왼쪽, 위 = 4
                elif c[i][j] == c[i-1][j]:
                    b[i-1][j-1] = 3 # 위 = 3
                else:
                    b[i-1][j-1] = 1 # 왼쪽 = 1
            
    printLCS(b, X, m-1, n-1, output)

def printLCS(b, X, i, j, output):
    if i == 0 or j == 0:
        print(output[::-1])
        return

    if b[i][j] == 2:
        # 대각선
        output = output + X[i]
        printLCS(b, X, i-1, j-1, output)
    elif b[i][j] == 4:
        temp = output
        # 양방향
        printLCS(b, X, i-1, j, temp)
        printLCS(b, X, i, j-1, output)
    elif b[i][j] == 3:
        printLCS(b, X, i-1, j, output) # 위
    else:
        printLCS(b, X, i, j-1, output) # 왼쪽

X = "ABCDEFDEF"
Y = "GBCDFEDEF"

LCS(X, Y, len(X), len(Y))