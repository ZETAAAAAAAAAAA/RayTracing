Matrix4f getRotationMatrix (float x,float y,float z){
    Matrix4f rotation = Matrix4f::Identity();
    
    Matrix4f rotationX;
    rotationX << 1,0,0,0,
                 0,cos(x),-sin(x),0,
                 0,sin(x),cos(x),0,
                 0,0,0,1;
    
    Matrix4f rotationY;
    rotationY << cos(y),0,sin(y),0,
                 0,1,0,0,
                 -sin(y),0,cos(y),0,
                 0,0,0,1;
    
    Matrix4f rotationZ;
    rotationZ << cos(z),-sin(z),0,0,
                 sin(z),cos(z),0,0,
                 0,0,1,0,
                 0,0,0,1;
    
    rotation = rotationZ * rotationX * rotationY;
    return rotation;
}

Matrix4f objectToWorldMatrix (Vector3f _rotation, Vector3f _scale, Vector3f _translation){

    Matrix4f model = Matrix4f::Identity();

    Matrix4f scale = Matrix4f::Identity();
    scale << _scale[0],0,0,0,
             0,_scale[1],0,0,0,
             0,0,_scale[2],0,
             0,0,0,1;

    Matrix4f rotation = getRotationMatrix(_rotation[0],_rotation[1],_rotation[2]);
    
    Matrix4f translation = Matrix4f::Identity();
    translation << 1,0,0,_translation[0],
                   0,1,0,_translation[1],
                   0,0,1,_translation[2],
                   0,0,0,1;
    
    model = translation * rotation * scale;
    return model;
}

// Camera Transform
Matrix4f worldToViewMatix (Vector3f _translation, Vector3f _rotation){
    Matrix4f view = Matrix4f::Identity();
    Matrix4f _view = Matrix4f::Identity();
    // right hand
    Matrix4f nsgats;
    nsgats << 1,0,0,0;
              0,1,0,0,
              0,0,-1,0,
              0,0,0,0;

    Matrix4f rotation = getRotationMatrix(_rotation[0],_rotation[1],_rotation[2]);
    
    Matrix4f translation = Matrix4f::Identity();
    translation << 1,0,0,_translation[0],
                   0,1,0,_translation[1],
                   0,0,1,_translation[2],
                   0,0,0,1;

    _view = rotation * translation;
    view = nsgats *_view;
    return view;
}

Matrix4f viewToClipMatrix(float FOV, float aspectRatio, float zNear, float zFar){
    Matrix4f projection = Matrix4f::Identity();
    projection << cot(FOV/2)/aspectRatio,0,0,0,
                  0,cot(FOV/2),0,0,
                  0,0,zNear+zFar/(zNear-zFar),2*zNear*zFar/(zNear-zFar),
                  0,0,-1,0;

    return projection;
}

//[0,1]
Vector2f computeScreenPos (Vector4f clipPos){
    Vector2f screenPos = {clipPos[0]/clipPos[3] * 0.5f + 0.5f, clipPos[1]/clipPos[3] * 0.5f + 0.5f};

    return screenPos;
}