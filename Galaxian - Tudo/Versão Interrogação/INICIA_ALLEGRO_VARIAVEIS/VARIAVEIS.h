#ifndef VARIAVEIS_H_INCLUDED
#define VARIAVEIS_H_INCLUDED


//!VARI�VEIS P/ OS INVASORES
            int matriz_invisivel[4][9];

            // criando uma matriz que servir� apenas para verificar se um invasor est� vivo para desenh�-lo ou n�o na tela
            //- caso vivo, sua posi��o ter� valor 1
            //- caso  morto ou em movimento, sua posi��o ter� valor 0  */

            // coluna e linha iniciais dos inimigos
        int inim_col = 70,
            inim_lin = 50,

            // coluna e linha iniciais do tiro dos inimigos
            tiro_lin = 900,
            tiro_col,
            dir=0,   // DIRE��O DO MOVIMENTO DOS INIMIGOS   0 = direita   1= esquerda
            rand_i, // para sortear a posi��o(em termos de linha da matriz_invisivel) do inimigo
            passo = 0,
            ci = 0,
            qtd_inimigos= 36,
            cont,
            pontos_nave = 0,
            SCORE,
            Y = 250,
            X = 340,
            ALTURA = 600,
            LARGURA = 900,
            OPCAO=0,
            c = 30,
            guard_i,guard_j,
            x = 340, y = 250;

            //vari�veis bool
    bool    repos_inimigo = false,
            game_over = false,
            MOVIMENTO = true,
            JogoMenu = true,
            MudarOpcao,
            EXIT = false,
            GAME = false,
            ComecarJogo = false,
            //!VARI�VEIS P/ A NAVE DO JOGADOR
            keys[5] = { false,false,false,false,false },
            FecharJanela = false, disparo = false;



#endif // VARIAVEIS_H_INCLUDED
