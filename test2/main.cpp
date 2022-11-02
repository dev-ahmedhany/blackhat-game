#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;
using namespace std;

int random(int min, int max) //range : [min, max]
{
   static bool first = true;
   if (first)
   {
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

int main()
{
    Clock clock = Clock();
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(1280, 720), "SFML works!", Style::Default, settings);
    window.setFramerateLimit(60);
    
    //sound
    Music music;
    if (!music.openFromFile("/Users/ahmedhany/projects/test app/test2/test2/cann.wav"))
        return -1;
    music.play();
    
    SoundBuffer buffer;
    if (!buffer.loadFromFile("/Users/ahmedhany/projects/test app/test2/test2/jump.wav"))
        return -1;
    Sound sound;
    sound.setBuffer(buffer);
    
    
    //textScore
    
    Font font;
    font.loadFromFile("/Users/ahmedhany/projects/test app/test2/test2/Roboto.ttf");
    Text textScore,textHeart,textGameOver;
    textScore.setFont(font);
    textScore.setCharacterSize(42);
    textScore.setFillColor(sf::Color::Red);

    textHeart.setFont(font);
    textHeart.setCharacterSize(42);
    textHeart.setFillColor(sf::Color::Red);
    textHeart.setPosition(1100.f,0.f);
    
    textGameOver.setFont(font);
    textGameOver.setCharacterSize(42);
    textGameOver.setFillColor(sf::Color::Red);
    textGameOver.setString("game over! ");
    textGameOver.setOrigin(textGameOver.getGlobalBounds().width/2, textGameOver.getGlobalBounds().height/2);
    textGameOver.setPosition(window.getSize().x/2,window.getSize().y/2);
        
    
    //user object
    int size = 50;
    Texture playerTexture,studentTexture,evilTexture;
    playerTexture.loadFromFile("/Users/ahmedhany/projects/test app/test2/test2/images/logo.png");
    Sprite player,student,evilPlayer;
    
    player.setTexture(playerTexture);
    player.setOrigin(size, size);
    player.setPosition(window.getSize().x/2, window.getSize().y/2);
    
    //student object
    studentTexture.loadFromFile("/Users/ahmedhany/projects/test app/test2/test2/images/student.png");
    student.setTexture(studentTexture);
    student.setPosition(random(size*2,window.getSize().x -size*2), random(size*2,window.getSize().y -size*2));
    
    // evail section
    CircleShape evilBall(20.f);
    evilBall.setFillColor(Color::Green);
    evilBall.setOrigin(20, 20);
    evilBall.setPosition(100, 100);
    
    evilTexture.loadFromFile("/Users/ahmedhany/projects/test app/test2/images/evel.jpg");
    evilPlayer.setTexture(evilTexture);
    evilPlayer.setOrigin(size, size);
    evilPlayer.setPosition(size, size);
    evilPlayer.setScale(0.15f, 0.15f);

    
    bool left = false, right = false,up=false ,down = false, dir = false;
    int evilBallXPosition = 0,score=0,heart = 5;
    float speed = 1,evilSpeed = 1;
    while (window.isOpen())
    {
        Time ElapsedTime = clock.restart();
        
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            
            //movment
            if (event.type == Event::KeyPressed){
                if(event.key.code == Keyboard::Left){
                    if(dir){
                        dir = false;
                        player.scale(-1, 1);
                    }
                    left = true;
                }
                 if(event.key.code == Keyboard::Right){
                     if(!dir){
                         dir = true;
                         player.scale(-1, 1);
                     }
                     right = true;
                }
                if(event.key.code == Keyboard::Up){
                    up = true;
                }
                if(event.key.code == Keyboard::Down){
                     down = true;
                }
            }
            if (event.type == Event::KeyReleased){
                if(event.key.code == Keyboard::Left){
                    left = false;
                }
                if(event.key.code == Keyboard::Up){
                    up = false;
                }
                 if(event.key.code == Keyboard::Right){
                     right = false;
                }
                
                if(event.key.code == Keyboard::Down){
                     down = false;
                }
            }
        }
        
        // evil stuff
        evilBallXPosition += evilSpeed*ElapsedTime.asMilliseconds();
        if (evilBallXPosition < 0 + evilBall.getRadius() || window.getSize().x - evilBall.getRadius() < evilBallXPosition)
        {
            evilSpeed *= -1;
        }

        evilBall.setPosition(evilBallXPosition, evilBall.getPosition().y);
        
        
        if ((player.getPosition().x > evilPlayer.getPosition().x && player.getPosition().y > evilPlayer.getPosition().y)){
            evilPlayer.move(2, 2);
        }else if ((player.getPosition().x < evilPlayer.getPosition().x && player.getPosition().y < evilPlayer.getPosition().y)){
            evilPlayer.move(-2,- 2);
        }else if ((player.getPosition().x > evilPlayer.getPosition().x && player.getPosition().y < evilPlayer.getPosition().y)){
            evilPlayer.move(2, -2);
        }else if ((player.getPosition().x < evilPlayer.getPosition().x && player.getPosition().y > evilPlayer.getPosition().y)){
            evilPlayer.move(-2, 2);
        }
        
        
        //logic
        
        float x = 0,y = 0;
        if (left){
            x = -speed;
        }
        if (right){
            x = speed;
        }
        if (up){
            y = -speed;
        }
        if (down){
            y = speed;
        }
        
        if (x && y) {
            x = x/1.5;
            y= y/1.5;
        }
        x = x*ElapsedTime.asMilliseconds();
        y = y *ElapsedTime.asMilliseconds();
        //left
        if(player.getPosition().x - size + x  <= 0){
            x = -(player.getPosition().x - size);
        }
        //right
        if(player.getPosition().x + size + x  >= window.getSize().x){
            x = window.getSize().x - player.getPosition().x - size;
        }
        //up
        if(player.getPosition().y - size + y  <= 0){
            y = -(player.getPosition().y - size);
        }
        //down
        if(player.getPosition().y + size + y  >=  window.getSize().y){
            y =  window.getSize().y - player.getPosition().y - size;
        }
        player.move(x, y);
        
        if(player.getGlobalBounds().intersects(student.getGlobalBounds())){
            Vector2f newPos = Vector2f(random(size*2, window.getSize().x -size*2), random(size*2, window.getSize().y -size*2));
            student.setPosition(newPos);
            evilBall.setPosition(evilBall.getPosition().x, random(50, window.getSize().y -50*2));
            score++;
            sound.play();
        }
        
        if(player.getGlobalBounds().intersects(evilBall.getGlobalBounds())){
            player.setPosition(window.getSize().x/2,window.getSize().y/2);
            evilBall.setPosition(100, 100);
            heart--;
            sound.play();
        }
        
        if(player.getGlobalBounds().intersects(evilPlayer.getGlobalBounds())){
            evilPlayer.setPosition(50,50);
            heart--;
            sound.play();
        }
        
        //<--draw here-->
        if(heart<=0){
            window.clear();
            
            textScore.setString("score: "+std::to_string(score));
            textHeart.setString("hearts: "+std::to_string(heart));
            window.draw(textScore);
            window.draw(textHeart);
            window.draw(textGameOver);
        } else{
            window.clear(Color::White);
            
            window.draw(player);
            window.draw(student);
            window.draw(evilPlayer);
            window.draw(evilBall);
            
            textScore.setString("score: "+std::to_string(score));
            textHeart.setString("hearts: "+std::to_string(heart));
            window.draw(textScore);
            window.draw(textHeart);
        }
        
        //<--end draw-->
        window.display();
    }
    return 0;
}
