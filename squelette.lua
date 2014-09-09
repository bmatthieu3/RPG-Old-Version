
if squelette:getChampVision() >= squelette:distance(joueur:getPosition()) then

    squelette:suivre(joueur)

    if joueur:estAttaquable(squelette) then
        squelette:attaquer(joueur)
    end
end







