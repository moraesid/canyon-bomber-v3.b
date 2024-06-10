# Canyon Bomber - Arquivado!

Trabalho final proposto para a matéria Programação e Desenvolvimento de Software 1, baseado na biblioteca Allegro 5.\
\
Versão final 3.b.

## Pacotes 

Existe uma release para Linux 64-bit, empacotada para Debian-Based, no entando é recomendável testar o projeto a partir de uma construção local, explicada a seguir.

## Construir Projeto
```
make 
make install
```
*Aviso: `make install` não instala binários nos diretórios padrões, apenas extrai recursos necessários à execução do programa no diretório de construção.*

### Executar

```
cd build/bin
./canyon-bomber
```

## Requisitos

 * Plataforma Linux (testado em Debian Bookworm 12.5)
 * Biblioteca Allegro 5
 * Gcc (construído localmente sob a versão 12)
 * Utilitários básicos (find, tar, gzip, etc)

## Créditos

Os materiais encontrados nos seguintes endereços contribuíram fortemente para o desenvolvimento do projeto:
  * [Rafael Toledo](https://rafaeltoledonet.wordpress.com/) - Tutoriais sobre a Biblioteca Allegro 5
  * [MikeGeigTV](https://www.youtube.com/@MikeGeigTV) - 2D Game Development
  * [CodingMadeEasy](https://www.youtube.com/@CodingMadeEasy) - C++ Allegro 5 Made Easy
  * [Raphael SC](https://www.youtube.com/@RAPHAELSC) - C++/ALLEGRO 5 JOGO DE NAVE
  * [Digmodification](https://digmodification.wordpress.com/) - Custom Crawl Creator
