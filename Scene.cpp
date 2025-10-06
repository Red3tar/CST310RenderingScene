#define GL_SILENCE_DEPRECATION
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

void drawChair(float centerX, float baseY, bool facingRight) {
    // DIMENSIONS - all the measurements
    float seatWidth = 0.28f;              
    float seatTopThickness = 0.04f;       
    float seatFrontEdgeHeight = 0.035f;   
    float backrestWidth = 0.26f;          
    float backrestHeight = 0.3f;         
    float backrestThickness = 0.025f;     
    float legWidth = 0.012f;              // MADE MUCH THINNER - thin metal rods
    float legHeight = 0.28f;              
    float perspectiveOffset = 0.08f;     
    float tiltOffset = 0.02f;             
    float tiltDir = facingRight ? -tiltOffset : tiltOffset;
    float legInset = 0.0f;               // Distance from seat edge to leg
    
    // Calculate leg positions at the 4 CORNERS of the seat
    // The seat itself has perspective - front is wider, back is narrower
    // So legs need to match where the seat corners actually are
    
    // FRONT leg positions (at the FRONT/BOTTOM edge of seat)
    float frontLeftLegX = centerX - seatWidth/2 + legInset + (facingRight ? perspectiveOffset : 0);
    float frontRightLegX = centerX + seatWidth/2 - legInset - (facingRight ? 0 : perspectiveOffset);
    
    // BACK leg positions (at the BACK/TOP edge of seat - narrower due to perspective)
    float backLeftLegX = centerX - seatWidth/2 + legInset + (facingRight ? 0 : perspectiveOffset);
    float backRightLegX = centerX + seatWidth/2 - legInset - (facingRight ? perspectiveOffset : 0);
    
    float frontLegY = baseY;                    // Front legs at base
    float backLegY = baseY + legHeight * 0.08f; // Back legs slightly higher (perspective)
    
    // ========== LEGS (4 vertical rectangles - proper 4-legged chair) ==========
    glColor3f(0.70f, 0.70f, 0.70f);  // Metallic gray
    
    if (facingRight) {
        // LEFT-FACING CHAIR - show left side legs prominently
        
        // SHAPE 1: FRONT-LEFT leg (most visible, front corner)
        glBegin(GL_QUADS);
            glVertex2f(frontLeftLegX, frontLegY);
            glVertex2f(frontLeftLegX + legWidth, frontLegY);
            glVertex2f(frontLeftLegX + legWidth, frontLegY + legHeight);
            glVertex2f(frontLeftLegX, frontLegY + legHeight);
        glEnd();
        
        // SHAPE 2: BACK-LEFT leg (visible, back corner on left side)
        glBegin(GL_QUADS);
            glVertex2f(backLeftLegX, backLegY);
            glVertex2f(backLeftLegX + legWidth, backLegY);
            glVertex2f(backLeftLegX + legWidth, backLegY + legHeight);
            glVertex2f(backLeftLegX, backLegY + legHeight);
        glEnd();
        
        // SHAPE 3: FRONT-RIGHT leg (behind seat, front corner on right)
        glColor3f(0.60f, 0.60f, 0.60f);  // Darker for depth
        glBegin(GL_QUADS);
            glVertex2f(frontRightLegX - legWidth, frontLegY);
            glVertex2f(frontRightLegX, frontLegY);
            glVertex2f(frontRightLegX, frontLegY + legHeight);
            glVertex2f(frontRightLegX - legWidth, frontLegY + legHeight);
        glEnd();
        
        // SHAPE 4: BACK-RIGHT leg (behind, back corner on right)
        glColor3f(0.55f, 0.55f, 0.55f);  // Darkest for furthest depth
        glBegin(GL_QUADS);
            glVertex2f(backRightLegX - legWidth, backLegY);
            glVertex2f(backRightLegX, backLegY);
            glVertex2f(backRightLegX, backLegY + legHeight);
            glVertex2f(backRightLegX - legWidth, backLegY + legHeight);
        glEnd();
        
    } else {
        // RIGHT-FACING CHAIR - show right side legs prominently
        
        // SHAPE 1: FRONT-RIGHT leg (most visible, front corner)
        glBegin(GL_QUADS);
            glVertex2f(frontRightLegX - legWidth, frontLegY);
            glVertex2f(frontRightLegX, frontLegY);
            glVertex2f(frontRightLegX, frontLegY + legHeight);
            glVertex2f(frontRightLegX - legWidth, frontLegY + legHeight);
        glEnd();
        
        // SHAPE 2: BACK-RIGHT leg (visible, back corner on right side)
        glBegin(GL_QUADS);
            glVertex2f(backRightLegX - legWidth, backLegY);
            glVertex2f(backRightLegX, backLegY);
            glVertex2f(backRightLegX, backLegY + legHeight);
            glVertex2f(backRightLegX - legWidth, backLegY + legHeight);
        glEnd();
        
        // SHAPE 3: FRONT-LEFT leg (behind seat, front corner on left)
        glColor3f(0.60f, 0.60f, 0.60f);  // Darker for depth
        glBegin(GL_QUADS);
            glVertex2f(frontLeftLegX, frontLegY);
            glVertex2f(frontLeftLegX + legWidth, frontLegY);
            glVertex2f(frontLeftLegX + legWidth, frontLegY + legHeight);
            glVertex2f(frontLeftLegX, frontLegY + legHeight);
        glEnd();
        
        // SHAPE 4: BACK-LEFT leg (behind, back corner on left)
        glColor3f(0.55f, 0.55f, 0.55f);  // Darkest for furthest depth
        glBegin(GL_QUADS);
            glVertex2f(backLeftLegX, backLegY);
            glVertex2f(backLeftLegX + legWidth, backLegY);
            glVertex2f(backLeftLegX + legWidth, backLegY + legHeight);
            glVertex2f(backLeftLegX, backLegY + legHeight);
        glEnd();
    }
    
    float seatY = baseY + legHeight;  // Where seat starts
    
    // ========== SEAT (3 parts: top, front edge, side edges) ==========
    
    // Calculate the 4 corners of the seat for consistency
    float seatBottomLeftX, seatBottomRightX, seatTopLeftX, seatTopRightX;
    if (facingRight) {
        seatBottomLeftX  = centerX - seatWidth/2 + perspectiveOffset;
        seatBottomRightX = centerX + seatWidth/2;
        seatTopRightX    = centerX + seatWidth/2 - perspectiveOffset;
        seatTopLeftX     = centerX - seatWidth/2;
    } else {
        seatBottomLeftX  = centerX - seatWidth/2;
        seatBottomRightX = centerX + seatWidth/2 - perspectiveOffset;
        seatTopRightX    = centerX + seatWidth/2;
        seatTopLeftX     = centerX - seatWidth/2 + perspectiveOffset;
    }
    
    float seatTopY = seatY + seatTopThickness;
    float seatFrontLowerY = seatY - seatFrontEdgeHeight;
    
    // SHAPE 5: Seat top surface (trapezoid - gives 3D perspective)
    glColor3f(0.35f, 0.35f, 0.35f);  // Light gray
    glBegin(GL_QUADS);
        glVertex2f(seatBottomLeftX, seatY);      // front-left corner
        glVertex2f(seatBottomRightX, seatY);     // front-right corner
        glVertex2f(seatTopRightX, seatTopY);     // back-right corner (narrower)
        glVertex2f(seatTopLeftX, seatTopY);      // back-left corner (narrower)
    glEnd();
    
    // SHAPE 6: Seat front edge (shows thickness)
    glColor3f(0.28f, 0.28f, 0.28f);  // Darker gray
    glBegin(GL_QUADS);
        glVertex2f(seatBottomLeftX, seatY);           // top-left
        glVertex2f(seatBottomRightX, seatY);          // top-right
        glVertex2f(seatBottomRightX, seatFrontLowerY); // bottom-right
        glVertex2f(seatBottomLeftX, seatFrontLowerY);  // bottom-left
    glEnd();
    
     // SHAPE 7: Seat left side edge (shows depth) - only draw for LEFT-facing chair
    if (facingRight) {
        glColor3f(0.26f, 0.26f, 0.26f);  // Even darker
        glBegin(GL_QUADS);
            glVertex2f(seatBottomLeftX, seatFrontLowerY);  // front-bottom
            glVertex2f(seatBottomLeftX, seatY);            // front-top
            glVertex2f(seatTopLeftX, seatTopY);            // back-top
            glVertex2f(seatTopLeftX, seatFrontLowerY + seatTopThickness); // back-bottom
        glEnd();
    }
    
    // SHAPE 8: Seat right side edge - only draw for RIGHT-facing chair
    if (!facingRight) {
        glColor3f(0.26f, 0.26f, 0.26f);
        glBegin(GL_QUADS);
            glVertex2f(seatBottomRightX, seatFrontLowerY);  // front-bottom
            glVertex2f(seatBottomRightX, seatY);            // front-top
            glVertex2f(seatTopRightX, seatTopY);            // back-top
            glVertex2f(seatTopRightX, seatFrontLowerY + seatTopThickness); // back-bottom
        glEnd();
    }
    // ========== BACKREST (3 parts: connection, main panel, top edge) ==========
    
    float backrestStartY = seatY + seatTopThickness;
    
    // Calculate where backrest attaches to seat back edge
    float seatBackLeft, seatBackRight;
    if (facingRight) {
        seatBackLeft = centerX - seatWidth/2;
        seatBackRight = centerX + seatWidth/2 - perspectiveOffset;
    } else {
        seatBackLeft = centerX - seatWidth/2 + perspectiveOffset;
        seatBackRight = centerX + seatWidth/2;
    }
    
    // SHAPE 9: Small connection piece (connects seat to backrest)
    float connectionHeight = 0.02f;
    glColor3f(0.32f, 0.32f, 0.32f);
    glBegin(GL_QUADS);
        glVertex2f(seatBackLeft, backrestStartY);              // bottom-left
        glVertex2f(seatBackRight, backrestStartY);             // bottom-right
        glVertex2f(seatBackRight, backrestStartY + connectionHeight); // top-right
        glVertex2f(seatBackLeft, backrestStartY + connectionHeight);  // top-left
    glEnd();
    
    // SHAPE 10: Main backrest panel (trapezoid that tilts backward)
    float backrestY = backrestStartY + connectionHeight;
    glColor3f(0.33f, 0.33f, 0.33f);
    glBegin(GL_QUADS);
        glVertex2f(seatBackLeft, backrestY);                    // bottom-left (attached to seat)
        glVertex2f(seatBackRight, backrestY);                   // bottom-right (attached to seat)
        glVertex2f(seatBackRight + tiltDir, backrestY + backrestHeight); // top-right (tilted back)
        glVertex2f(seatBackLeft + tiltDir, backrestY + backrestHeight);  // top-left (tilted back)
    glEnd();
    
    // SHAPE 11: Backrest top edge (visible because of backward tilt)
    glColor3f(0.29f, 0.29f, 0.29f);
    glBegin(GL_QUADS);
        glVertex2f(seatBackLeft + tiltDir, backrestY + backrestHeight);  // bottom-left
        glVertex2f(seatBackRight + tiltDir, backrestY + backrestHeight); // bottom-right
        glVertex2f(seatBackRight + tiltDir, backrestY + backrestHeight + backrestThickness); // top-right
        glVertex2f(seatBackLeft + tiltDir, backrestY + backrestHeight + backrestThickness);  // top-left
    glEnd();
    
    // ========== PILLOW (1 rounded rectangle on backrest) ==========
    
    glColor3f(0.0f, 0.0f, 0.5f);  // Navy blue
    
    float pillowWidth = 0.22f;
    float pillowHeight = 0.22f;
    float pillowY = backrestY + 0.08f;  // Position on backrest
    float corner = 0.04f;  // Corner rounding
    
    float pillowCenterX = centerX + (tiltDir * 0.3f);  // Adjust for backrest tilt
    
    // SHAPE 12: Pillow (polygon with rounded corners - 20+ vertices)
    glBegin(GL_POLYGON);
        // Bottom edge
        glVertex2f(pillowCenterX - pillowWidth/2 + corner, pillowY - pillowHeight/2);
        glVertex2f(pillowCenterX - pillowWidth/2 + corner * 1.5f, pillowY - pillowHeight/2);
        glVertex2f(pillowCenterX + pillowWidth/2 - corner * 1.5f, pillowY - pillowHeight/2);
        glVertex2f(pillowCenterX + pillowWidth/2 - corner, pillowY - pillowHeight/2);
        
        // Bottom-right corner (curved)
        glVertex2f(pillowCenterX + pillowWidth/2, pillowY - pillowHeight/2 + corner);
        
        // Right edge
        glVertex2f(pillowCenterX + pillowWidth/2, pillowY - pillowHeight/2 + corner * 1.5f);
        glVertex2f(pillowCenterX + pillowWidth/2, pillowY + pillowHeight/2 - corner * 1.5f);
        
        // Top-right corner (curved)
        glVertex2f(pillowCenterX + pillowWidth/2, pillowY + pillowHeight/2 - corner);
        
        // Top edge
        glVertex2f(pillowCenterX + pillowWidth/2 - corner, pillowY + pillowHeight/2);
        glVertex2f(pillowCenterX + pillowWidth/2 - corner * 1.5f, pillowY + pillowHeight/2);
        glVertex2f(pillowCenterX - pillowWidth/2 + corner * 1.5f, pillowY + pillowHeight/2);
        glVertex2f(pillowCenterX - pillowWidth/2 + corner, pillowY + pillowHeight/2);
        
        // Top-left corner (curved)
        glVertex2f(pillowCenterX - pillowWidth/2, pillowY + pillowHeight/2 - corner);
        
        // Left edge
        glVertex2f(pillowCenterX - pillowWidth/2, pillowY + pillowHeight/2 - corner * 1.5f);
        glVertex2f(pillowCenterX - pillowWidth/2, pillowY - pillowHeight/2 + corner * 1.5f);
        
        // Bottom-left corner (curved)
        glVertex2f(pillowCenterX - pillowWidth/2, pillowY - pillowHeight/2 + corner);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    //============ BACKGROUND ================================
    
    // Draw the upper half light gray
    glColor3f(0.7f, 0.7f, 0.7f);  // Light gray color
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
    glEnd();
    
    // Draw the lower half light brown
    glColor3f(0.885f, 0.84f, 0.64f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(-1.0f, 0.0f);
    glEnd();
    
    // Darker transition strip
    glColor3f(0.75f, 0.7f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, 0.05f);
        glVertex2f(1.0f, 0.05f);
        glVertex2f(1.0f, -0.05f);
        glVertex2f(-1.0f, -0.05f);
    glEnd();
    
    //=================== CHAIRS (PROPERLY ALIGNED) ========================
    
    // Left chair - positioned to the left of the round table
    drawChair(-0.65f, -0.20f, true);  // facingRight = true
    
    // Right chair - positioned to the right of the round table
    drawChair(0.65f, -0.20f, false);  // facingRight = false
    
    //====================== RECTANGLE TABLE ==============================
    
    float offset = -0.15f;
   
    // Draw the trapezoid (table top)
    glColor3f(0.82f, 0.71f, 0.55f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.7f, offset);
        glVertex2f(0.7f, offset);
        glVertex2f(0.9f, offset - 0.3f);
        glVertex2f(-0.9f, offset - 0.3f);
    glEnd();
    
    // Draw rectangle (table body)
    glColor3f(0.69f, 0.58f, 0.43f);
    glBegin(GL_QUADS);
        glVertex2f(-0.9f, offset - 0.3f);
        glVertex2f(0.9f, offset - 0.3f);
        glVertex2f(0.9f, offset - 0.7f);
        glVertex2f(-0.9f, offset - 0.7f);
    glEnd();
    
    // Draw inner rectangle
    glColor3f(0.55f, 0.45f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-0.8f, offset - 0.35f);
        glVertex2f(0.8f, offset - 0.35f);
        glVertex2f(0.8f, offset - 0.65f);
        glVertex2f(-0.8f, offset - 0.65f);
    glEnd();
    
    // Legs
    glColor3f(0.5f, 0.5f, 0.5f);

    // Left leg
    glBegin(GL_QUADS);
        glVertex2f(-0.80f, offset - 0.7f);
        glVertex2f(-0.66f, offset - 0.7f);
        glVertex2f(-0.66f, offset - 0.82f);
        glVertex2f(-0.80f, offset - 0.82f);
    glEnd();

    // Right leg
    glBegin(GL_QUADS);
        glVertex2f(0.66f, offset - 0.7f);
        glVertex2f(0.80f, offset - 0.7f);
        glVertex2f(0.80f, offset - 0.82f);
        glVertex2f(0.66f, offset - 0.82f);
    glEnd();
    
    //==================== CIRCLE TABLE ===========================
    
    // Pedestal
    glColor3f(0.75f, 0.75f, 0.75f);
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, offset);
        glVertex2f(0.05f, offset);
        glVertex2f(0.05f, offset + 0.45f);
        glVertex2f(-0.05f, offset + 0.45f);
    glEnd();
    
    // Table top rim
    glColor3f(0.33f, 0.33f, 0.33f);
    int numSegments = 100;
    float radiusX = 0.55f;
    float radiusY = 0.07f;
    float ovalCenterY = offset + 0.45f + radiusY;

    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++) {
        float angle = 2.0f * 3.14159f * i / numSegments;
        float x = radiusX * cos(angle);
        float y = radiusY * sin(angle);
        glVertex2f(x, ovalCenterY + y);
    }
    glEnd();
    
    // Table top surface
    glColor3f(0.83f, 0.83f, 0.83f);
    float innerRadiusX = 0.52f;
    float innerRadiusY = 0.05f;
    float redOvalOffset = 0.02f;

    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++) {
        float angle = 2.0f * 3.14159f * i / numSegments;
        float x = innerRadiusX * cos(angle);
        float y = innerRadiusY * sin(angle);
        glVertex2f(x, ovalCenterY + y + redOvalOffset);
    }
    glEnd();
    
    //=================== BOOK =========================
    
    glColor3f(0.0f, 0.0f, 0.0f);
    float rectWidth = 0.22f;
    float rectHeight = 0.28f;
    float rectOffsetY = ovalCenterY + radiusY - 0.05f;
    float rectOffsetX = 0.25f;

    glBegin(GL_QUADS);
        glVertex2f(-rectWidth / 2 + rectOffsetX, rectOffsetY);
        glVertex2f(rectWidth / 2 + rectOffsetX, rectOffsetY);
        glVertex2f(rectWidth / 2 + rectOffsetX, rectOffsetY + rectHeight);
        glVertex2f(-rectWidth / 2 + rectOffsetX, rectOffsetY + rectHeight);
    glEnd();

    //============= SWITCH =====================
    
    glColor3f(1.0f, 1.0f, 1.0f);
    float SWrectWidth = 0.06f;
    float SWrectHeight = 0.09f;
    float SWrectOffsetY = ovalCenterY + radiusY - 0.3f;
    float SWrectOffsetX = -0.25f;

    glBegin(GL_QUADS);
        glVertex2f(-SWrectWidth / 2 + SWrectOffsetX, SWrectOffsetY);
        glVertex2f(SWrectWidth / 2 + SWrectOffsetX, SWrectOffsetY);
        glVertex2f(SWrectWidth / 2 + SWrectOffsetX, SWrectOffsetY + SWrectHeight);
        glVertex2f(-SWrectWidth / 2 + SWrectOffsetX, SWrectOffsetY + SWrectHeight);
    glEnd();
    
    //============== SOCKET =====================
    
    glColor3f(1.0f, 1.0f, 1.0f);
    float LrectWidth = 0.05f;
    float LrectHeight = 0.08f;
    float LrectOffsetY = ovalCenterY + radiusY + 0.2f;
    float LrectOffsetX = 0.85f;

    glBegin(GL_QUADS);
        glVertex2f(-LrectWidth / 2 + LrectOffsetX, LrectOffsetY);
        glVertex2f(LrectWidth / 2 + LrectOffsetX, LrectOffsetY);
        glVertex2f(LrectWidth / 2 + LrectOffsetX, LrectOffsetY + LrectHeight);
        glVertex2f(-LrectWidth / 2 + LrectOffsetX, LrectOffsetY + LrectHeight);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 400);
    glutCreateWindow("Scene with 4-Legged Chairs");

    glutDisplayFunc(display);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glutMainLoop();
    return 0;
}