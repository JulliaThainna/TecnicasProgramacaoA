#ifndef VARIAVEIS_H_INCLUDED
#define VARIAVEIS_H_INCLUDED


//!VARI�VEIS P/ OS INVASORES
            int matriz_invisivel[5][7];

            // criando uma matriz que servir� apenas para verificar se um invasor est� vivo para desenh�-lo ou n�o na tela
            //- caso vivo, sua posi��o ter� valor 1
            //- caso  morto ou em movimento, sua posi��o ter� valor 0  */

            // coluna e linha iniciais dos inimigos
			int inim_col = 70,
				inim_lin = 50,
				// coluna e linha iniciais do tiro dos inimigos
				tiro_lin = 900,
				tiro_col,
				dir = 0,   // DIRE��O DO MOVIMENTO DOS INIMIGOS   0 = direita   1= esquerda
				rand_i, // para sortear a posi��o(em termos de linha da matriz_invisivel) do inimigo
				passo = 0,
				ci = 0,
				qtd_inimigos = 36,
				cont,
				pontos_nave = 0,
				SCORE = 0,
				ALTURA = 600,
				LARGURA = 900,
				opcao = 0,
				c = 30,
				lugar [5],
				guard_i, guard_j,
				direction = 0,
				x = 340,
				y = 250,
				z = 250,
				xnave = 340,
				i = 0,
				j = 0;

            //vari�veis bool
		bool      repos_inimigo = false,
				secundario = false;
				movimento = true,
				jaSomou = false,
				menu = true,
				gameOver = false,
				mudarOpcao = false,
				fechar = false,
				jogo = false,
				ComecarJogo = false,
				//!VARI�VEIS P/ A NAVE DO JOGADOR
				keys[5] = { false,false,false,false,false },
				disparo = false;

#endif // VARIAVEIS_H_INCLUDED
