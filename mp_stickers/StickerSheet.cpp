#include <iostream>
#include "StickerSheet.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
 namespace cs225{
    StickerSheet::StickerSheet(const Image &picture, unsigned max){
        picture_= picture;
        vectptr.resize(max);
        xcord.resize(max);
        ycord.resize(max);
        max_ = max;
    }
 }
    StickerSheet::StickerSheet(const StickerSheet &other){
        vectptr = other.vectptr;
        max_ = other.max_;
        picture_ = other.picture_;
        xcord = other.xcord;
        ycord = other.ycord; 
     }



    const StickerSheet & StickerSheet::operator= (const StickerSheet & other){
        if(this != &other){
            picture_=other.picture_;
            max_=other.max_;
            vectptr=other.vectptr;
            xcord = other.xcord;
            ycord=other.ycord;
        }

        return *this;
    }
    int StickerSheet::addSticker(Image &sticker, int x , int y){
        for(unsigned i=0; i < vectptr.size();i++){
            if(vectptr[i]==NULL){
                vectptr[i]= &sticker;
                ycord[i]= y;
                xcord[i]= x;
                return i;
            }
        }
        vectptr.push_back(&sticker);
        xcord.push_back(x);
        ycord.push_back(y);
        max_ = max_ + 1;
        return (vectptr.size()-1) ;
    }

    void StickerSheet::changeMaxStickers(unsigned max){
        max_ = max;
        vectptr.resize(max);
        xcord.resize(max);
        ycord.resize(max);
    }

    Image * StickerSheet::getSticker( unsigned index){
        if(index < 0 || index > vectptr.size()){
            return NULL;
        }
        else{
                return vectptr[index];
            }
        }

    int StickerSheet::layers() const{
        return vectptr.size();
    }
    void StickerSheet::removeSticker(unsigned index){ 
        if(index >= 0 && index < vectptr.size() ){
            if(vectptr[index] !=NULL) {
            vectptr[index] = NULL;
            xcord[index] = -1 ;
            ycord[index] = -1 ;
        }
        return;
    }
    }
    bool StickerSheet::translate(unsigned index, int x, int y){
        if(index >= 0 && index < vectptr.size()){
            if(vectptr[index] != NULL){
            ycord[index] = y;
            xcord[index] = x;
            return true;
            }
        }
         return false;
        }
    int StickerSheet::setStickerAtLayer(Image & sticker, unsigned layer, int x, int y){
         if (layer >= 0 && layer < vectptr.size() ){
                xcord[layer] = x;
                ycord[layer] = y;
                vectptr[layer] = &sticker;
                return layer;
            }
        else{
            return -1;
        }
    }
    Image StickerSheet::render()const{
        int max1 = picture_.width();
        int max2 = picture_.height();
        int min1 = 0;
        int min2 = 0;
        
        for(size_t i = 0; i< max_; i++){
            if(vectptr.at(i) !=NULL){
                if(xcord[i]<  min1){
                    min1 = xcord[i];
                }
                 if(ycord[i]< min2){
                    min2 = ycord[i];
                }
                 if(xcord[i] + vectptr[i]->width() > (unsigned) max1){
                    max1 = xcord[i] + vectptr[i]->width();
                }
                 if(ycord[i] + vectptr[i]->height() > (unsigned) max2){
                    max2 = ycord[i] + vectptr[i]->height();
                }
            }
        }
        unsigned int imagewidth = max1 - min1 ;
        unsigned int imageheight = max2 - min2 ;
        Image render(imagewidth, imageheight);
        // render.width();
        int baseimagey = abs(min2) ;
        int baseimagex = abs(min1) ;
        for(unsigned int i = baseimagex; i < baseimagex + picture_.width() ;i++){
            for(unsigned int j = baseimagey ; j < (baseimagey + picture_.height()) ;j++){
                render.getPixel(i,j) = picture_.getPixel(i - baseimagex, j - baseimagey);
            }   
        }
        for (size_t len = 0; len < vectptr.size();len++){
            if(vectptr.at(len) != NULL){
                for(unsigned int i = baseimagex + xcord[len]; i < baseimagex + xcord[len] + vectptr[len]->width();i++){
                    for(unsigned int j = baseimagey + ycord[len]; j < baseimagey + ycord[len] + vectptr[len]->height();j++){
                        if((vectptr[len] -> getPixel(i - xcord[len] - baseimagex,j - ycord[len] - baseimagey)).a != 0){
                            render.getPixel(i,j) = vectptr[len]->getPixel(i - xcord[len] - baseimagex,j - ycord[len] - baseimagey);
                        }
                    }
                }
            }
        }
        return render;
    };

