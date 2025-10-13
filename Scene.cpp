#define GL_SILENCE_DEPRECATION
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

// Camera controls
float cameraX = 0.0f;
float cameraY = 0.0f;
float zoomLevel = 1.0f;

// Camera boundaries
const float MIN_X = -0.5f;
const float MAX_X = 0.5f;
const float MIN_Y = -1.0f;
const float MAX_Y = 1.0f;

void drawChair(float centerX, float baseY, bool facingRight) {
    float seatWidth = 0.28f;              
    float seatTopThickness = 0.04f;       
    float seatFrontEdgeHeight = 0.035f;   
    float backrestWidth = 0.26f;          
    float backrestHeight = 0.3f;         
    float backrestThickness = 0.025f;     
    float legWidth = 0.012f;
    float legHeight = 0.28f;              
    float perspectiveOffset = 0.08f;     
    float tiltOffset = 0.02f;             
    float tiltDir = facingRight ? -tiltOffset : tiltOffset;
    float legInset = 0.0f;
    
    float frontLeftLegX = centerX - seatWidth/2 + legInset + (facingRight ? perspectiveOffset : 0);
    float frontRightLegX = centerX + seatWidth/2 - legInset - (facingRight ? 0 : perspectiveOffset);
    float backLeftLegX = centerX - seatWidth/2 + legInset + (facingRight ? 0 : perspectiveOffset);
    float backRightLegX = centerX + seatWidth/2 - legInset - (facingRight ? perspectiveOffset : 0);
    
    float frontLegY = baseY;
    float backLegY = baseY + legHeight * 0.08f;
    
    // ========== LEGS (metallic silver) ==========
    glColor3f(0.75f, 0.75f, 0.78f);  // Silvery metal
    
    if (facingRight) {
        glBegin(GL_QUADS);
            glVertex2f(frontLeftLegX, frontLegY);
            glVertex2f(frontLeftLegX + legWidth, frontLegY);
            glVertex2f(frontLeftLegX + legWidth, frontLegY + legHeight);
            glVertex2f(frontLeftLegX, frontLegY + legHeight);
        glEnd();
        
        glBegin(GL_QUADS);
            glVertex2f(backLeftLegX, backLegY);
            glVertex2f(backLeftLegX + legWidth, backLegY);
            glVertex2f(backLeftLegX + legWidth, backLegY + legHeight);
            glVertex2f(backLeftLegX, backLegY + legHeight);
        glEnd();
        
        glColor3f(0.65f, 0.65f, 0.68f);
        glBegin(GL_QUADS);
            glVertex2f(frontRightLegX - legWidth, frontLegY);
            glVertex2f(frontRightLegX, frontLegY);
            glVertex2f(frontRightLegX, frontLegY + legHeight);
            glVertex2f(frontRightLegX - legWidth, frontLegY + legHeight);
        glEnd();
        
        glColor3f(0.60f, 0.60f, 0.63f);
        glBegin(GL_QUADS);
            glVertex2f(backRightLegX - legWidth, backLegY);
            glVertex2f(backRightLegX, backLegY);
            glVertex2f(backRightLegX, backLegY + legHeight);
            glVertex2f(backRightLegX - legWidth, backLegY + legHeight);
        glEnd();
    } else {
        glBegin(GL_QUADS);
            glVertex2f(frontRightLegX - legWidth, frontLegY);
            glVertex2f(frontRightLegX, frontLegY);
            glVertex2f(frontRightLegX, frontLegY + legHeight);
            glVertex2f(frontRightLegX - legWidth, frontLegY + legHeight);
        glEnd();
        
        glBegin(GL_QUADS);
            glVertex2f(backRightLegX - legWidth, backLegY);
            glVertex2f(backRightLegX, backLegY);
            glVertex2f(backRightLegX, backLegY + legHeight);
            glVertex2f(backRightLegX - legWidth, backLegY + legHeight);
        glEnd();
        
        glColor3f(0.65f, 0.65f, 0.68f);
        glBegin(GL_QUADS);
            glVertex2f(frontLeftLegX, frontLegY);
            glVertex2f(frontLeftLegX + legWidth, frontLegY);
            glVertex2f(frontLeftLegX + legWidth, frontLegY + legHeight);
            glVertex2f(frontLeftLegX, frontLegY + legHeight);
        glEnd();
        
        glColor3f(0.60f, 0.60f, 0.63f);
        glBegin(GL_QUADS);
            glVertex2f(backLeftLegX, backLegY);
            glVertex2f(backLeftLegX + legWidth, backLegY);
            glVertex2f(backLeftLegX + legWidth, backLegY + legHeight);
            glVertex2f(backLeftLegX, backLegY + legHeight);
        glEnd();
    }
    
    float seatY = baseY + legHeight;
    
    // ========== SEAT (dark gray plastic) ==========
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
    
    glColor3f(0.25f, 0.25f, 0.25f);  // Dark gray seat
    glBegin(GL_QUADS);
        glVertex2f(seatBottomLeftX, seatY);
        glVertex2f(seatBottomRightX, seatY);
        glVertex2f(seatTopRightX, seatTopY);
        glVertex2f(seatTopLeftX, seatTopY);
    glEnd();
    
    glColor3f(0.20f, 0.20f, 0.20f);
    glBegin(GL_QUADS);
        glVertex2f(seatBottomLeftX, seatY);
        glVertex2f(seatBottomRightX, seatY);
        glVertex2f(seatBottomRightX, seatFrontLowerY);
        glVertex2f(seatBottomLeftX, seatFrontLowerY);
    glEnd();
    
    if (facingRight) {
        glColor3f(0.18f, 0.18f, 0.18f);
        glBegin(GL_QUADS);
            glVertex2f(seatBottomLeftX, seatFrontLowerY);
            glVertex2f(seatBottomLeftX, seatY);
            glVertex2f(seatTopLeftX, seatTopY);
            glVertex2f(seatTopLeftX, seatFrontLowerY + seatTopThickness);
        glEnd();
    }
    
    if (!facingRight) {
        glColor3f(0.18f, 0.18f, 0.18f);
        glBegin(GL_QUADS);
            glVertex2f(seatBottomRightX, seatFrontLowerY);
            glVertex2f(seatBottomRightX, seatY);
            glVertex2f(seatTopRightX, seatTopY);
            glVertex2f(seatTopRightX, seatFrontLowerY + seatTopThickness);
        glEnd();
    }
    
    // ========== BACKREST ==========
    float backrestStartY = seatY + seatTopThickness;
    
    float seatBackLeft, seatBackRight;
    if (facingRight) {
        seatBackLeft = centerX - seatWidth/2;
        seatBackRight = centerX + seatWidth/2 - perspectiveOffset;
    } else {
        seatBackLeft = centerX - seatWidth/2 + perspectiveOffset;
        seatBackRight = centerX + seatWidth/2;
    }
    
    float connectionHeight = 0.02f;
    glColor3f(0.23f, 0.23f, 0.23f);
    glBegin(GL_QUADS);
        glVertex2f(seatBackLeft, backrestStartY);
        glVertex2f(seatBackRight, backrestStartY);
        glVertex2f(seatBackRight, backrestStartY + connectionHeight);
        glVertex2f(seatBackLeft, backrestStartY + connectionHeight);
    glEnd();
    
    float backrestY = backrestStartY + connectionHeight;
    glColor3f(0.24f, 0.24f, 0.24f);
    glBegin(GL_QUADS);
        glVertex2f(seatBackLeft, backrestY);
        glVertex2f(seatBackRight, backrestY);
        glVertex2f(seatBackRight + tiltDir, backrestY + backrestHeight);
        glVertex2f(seatBackLeft + tiltDir, backrestY + backrestHeight);
    glEnd();
    
    glColor3f(0.21f, 0.21f, 0.21f);
    glBegin(GL_QUADS);
        glVertex2f(seatBackLeft + tiltDir, backrestY + backrestHeight);
        glVertex2f(seatBackRight + tiltDir, backrestY + backrestHeight);
        glVertex2f(seatBackRight + tiltDir, backrestY + backrestHeight + backrestThickness);
        glVertex2f(seatBackLeft + tiltDir, backrestY + backrestHeight + backrestThickness);
    glEnd();
    
    // ========== PILLOW (brighter navy blue) ==========
    glColor3f(0.25f, 0.30f, 0.50f);  // Brighter navy blue to match photo
    
    float pillowWidth = 0.22f;
    float pillowHeight = 0.22f;
    float pillowY = backrestY + 0.08f;
    float corner = 0.04f;
    
    float pillowCenterX = centerX + (tiltDir * 0.3f);
    
    glBegin(GL_POLYGON);
        glVertex2f(pillowCenterX - pillowWidth/2 + corner, pillowY - pillowHeight/2);
        glVertex2f(pillowCenterX - pillowWidth/2 + corner * 1.5f, pillowY - pillowHeight/2);
        glVertex2f(pillowCenterX + pillowWidth/2 - corner * 1.5f, pillowY - pillowHeight/2);
        glVertex2f(pillowCenterX + pillowWidth/2 - corner, pillowY - pillowHeight/2);
        glVertex2f(pillowCenterX + pillowWidth/2, pillowY - pillowHeight/2 + corner);
        glVertex2f(pillowCenterX + pillowWidth/2, pillowY - pillowHeight/2 + corner * 1.5f);
        glVertex2f(pillowCenterX + pillowWidth/2, pillowY + pillowHeight/2 - corner * 1.5f);
        glVertex2f(pillowCenterX + pillowWidth/2, pillowY + pillowHeight/2 - corner);
        glVertex2f(pillowCenterX + pillowWidth/2 - corner, pillowY + pillowHeight/2);
        glVertex2f(pillowCenterX + pillowWidth/2 - corner * 1.5f, pillowY + pillowHeight/2);
        glVertex2f(pillowCenterX - pillowWidth/2 + corner * 1.5f, pillowY + pillowHeight/2);
        glVertex2f(pillowCenterX - pillowWidth/2 + corner, pillowY + pillowHeight/2);
        glVertex2f(pillowCenterX - pillowWidth/2, pillowY + pillowHeight/2 - corner);
        glVertex2f(pillowCenterX - pillowWidth/2, pillowY + pillowHeight/2 - corner * 1.5f);
        glVertex2f(pillowCenterX - pillowWidth/2, pillowY - pillowHeight/2 + corner * 1.5f);
        glVertex2f(pillowCenterX - pillowWidth/2, pillowY - pillowHeight/2 + corner);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Apply camera transformation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(zoomLevel, zoomLevel, 1.0f);
    glTranslatef(cameraX, cameraY, 0.0f);
    
    //============ BACKGROUND (EXTENDED) ================================
    // Wall (upper half) - lighter gray to match photo
    glBegin(GL_QUADS);
        glColor3f(0.72f, 0.72f, 0.72f);  // Lighter gray at top
        glVertex2f(-5.0f, 3.0f);
        glVertex2f(5.0f, 3.0f);
        glColor3f(0.76f, 0.76f, 0.76f);  // Even lighter near horizon
        glVertex2f(5.0f, 0.0f);
        glVertex2f(-5.0f, 0.0f);
    glEnd();
    
    // Floor - lighter tan/beige to match photo
    glBegin(GL_QUADS);
        glColor3f(0.68f, 0.63f, 0.56f);  // Tan at bottom
        glVertex2f(-5.0f, -3.0f);
        glVertex2f(5.0f, -3.0f);
        glColor3f(0.72f, 0.67f, 0.60f);  // Lighter tan near horizon
        glVertex2f(5.0f, 0.0f);
        glVertex2f(-5.0f, 0.0f);
    glEnd();
    
    // Add carpet pattern (subtle horizontal lines)
    glColor3f(0.65f, 0.60f, 0.53f);
    glLineWidth(1.0f);
    for (float y = -2.8f; y < 0.0f; y += 0.12f) {
        glBegin(GL_LINES);
            glVertex2f(-5.0f, y);
            glVertex2f(5.0f, y);
        glEnd();
    }
    
    // Baseboard - darker brown
    glColor3f(0.50f, 0.42f, 0.30f);
    glBegin(GL_QUADS);
        glVertex2f(-5.0f, 0.08f);
        glVertex2f(5.0f, 0.08f);
        glVertex2f(5.0f, -0.03f);
        glVertex2f(-5.0f, -0.03f);
    glEnd();
    
    //=========================Light Shading (Wall Shadows)========================
    
    // Triangle 1 (right side shadow - fully extended)
    glColor3f(0.55f, 0.55f, 0.55f);
    glBegin(GL_TRIANGLES);
        float triHeightVal = 2.5f;  // Much larger height
        float triBaseY = 2.2f;  // Lowered from 3.0f
        float triLeftBaseX = -3.0f;  // Extended far left
        float triRightBaseX = 5.0f;  // Extended to right edge
        float triCenterX = (triLeftBaseX + triRightBaseX) / 2.0f;
        float triCenterY = triBaseY - triHeightVal / 3.0f;
        float triOrigTopX = triCenterX;
        float triOrigTopY = triBaseY;
        float triOrigLeftX = triLeftBaseX;
        float triOrigLeftY = triBaseY - triHeightVal;
        float triOrigRightX = triRightBaseX;
        float triOrigRightY = triBaseY - triHeightVal;
        float triRotTopX = 2 * triCenterX - triOrigTopX;
        float triRotTopY = 2 * triCenterY - triOrigTopY;
        float triRotLeftX = 2 * triCenterX - triOrigLeftX;
        float triRotLeftY = 2 * triCenterY - triOrigLeftY;
        float triRotRightX = 2 * triCenterX - triOrigRightX;
        float triRotRightY = 2 * triCenterY - triOrigRightY;
        glVertex2f(triRotTopX, triRotTopY);
        glVertex2f(triRotRightX, triRotRightY);
        glVertex2f(triRotLeftX, triRotLeftY);
    glEnd();

    // Triangle 2 (left side shadow - fully extended)
    glBegin(GL_TRIANGLES);
        float heightTri2 = 2.5f;  // Much larger height
        float topY = 2.2f;  // Lowered from 3.0f
        float rightX = 3.5f;  // Moved right (was 3.0f)
        glVertex2f(-4.5f, topY);  // Moved right (was -5.0f)
        glVertex2f(-4.5f, topY - heightTri2);
        glVertex2f(rightX, topY);
    glEnd();
    //=================== CHAIRS ========================
    drawChair(-0.65f, -0.20f, true);
    drawChair(0.65f, -0.20f, false);
    
    //====================== RECTANGLE TABLE (front table) ==============================
    float offset = -0.15f;
   
    // Table top with wood texture
    glColor3f(0.82f, 0.75f, 0.60f);  // Light wood
    glBegin(GL_POLYGON);
        glVertex2f(-0.7f, offset);
        glVertex2f(0.7f, offset);
        glVertex2f(0.9f, offset - 0.3f);
        glVertex2f(-0.9f, offset - 0.3f);
    glEnd();
    
    // Wood grain lines
    glColor3f(0.78f, 0.71f, 0.56f);
    for (int i = 0; i < 5; i++) {
        float x = -0.6f + i * 0.3f;
        glBegin(GL_LINES);
            glVertex2f(x, offset - 0.02f);
            glVertex2f(x + 0.15f, offset - 0.28f);
        glEnd();
    }
    
    // Side of table
    glColor3f(0.72f, 0.65f, 0.52f);
    glBegin(GL_QUADS);
        glVertex2f(-0.9f, offset - 0.3f);
        glVertex2f(0.9f, offset - 0.3f);
        glVertex2f(0.9f, offset - 0.7f);
        glVertex2f(-0.9f, offset - 0.7f);
    glEnd();
    
    // Inner rectangle (shelf)
    glColor3f(0.65f, 0.58f, 0.48f);
    glBegin(GL_QUADS);
        glVertex2f(-0.8f, offset - 0.35f);
        glVertex2f(0.8f, offset - 0.35f);
        glVertex2f(0.8f, offset - 0.65f);
        glVertex2f(-0.8f, offset - 0.65f);
    glEnd();
    
    //===============Inside Shadow (trapezoid in shelf)================
    float baseY_trap = offset - 0.65f;
    float height_trap = (0.65f - 0.35f) / 2 + 0.05;
    float topY_trap = baseY_trap + height_trap;
    float leftX_trap = -0.8f;
    float rightX_trap = 0.8f;
    float topLeftX_trap = -0.7f;
    float topRightX_trap = 0.7f;

    glColor3f(0.50f, 0.40f, 0.25f);
    glBegin(GL_POLYGON);
        glVertex2f(leftX_trap, baseY_trap);
        glVertex2f(rightX_trap, baseY_trap);
        glVertex2f(topRightX_trap, topY_trap);
        glVertex2f(topLeftX_trap, topY_trap);
    glEnd();

    //=======================Table Shadow (under front table)===========================
    glColor3f(0.55f, 0.55f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.66f, offset - 0.7f);
        glVertex2f(0.87f, offset - 0.7f);
        glVertex2f(0.87f, offset - 0.78f);
        glVertex2f(-0.66f, offset - 0.78f);
    glEnd();
    
    // Legs with metallic gray
    glColor3f(0.75f, 0.75f, 0.75f);
    glBegin(GL_QUADS);
        glVertex2f(-0.80f, offset - 0.7f);
        glVertex2f(-0.66f, offset - 0.7f);
        glVertex2f(-0.66f, offset - 0.82f);
        glVertex2f(-0.80f, offset - 0.82f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.66f, offset - 0.7f);
        glVertex2f(0.80f, offset - 0.7f);
        glVertex2f(0.80f, offset - 0.82f);
        glVertex2f(0.66f, offset - 0.82f);
    glEnd();
    
    //==================== CIRCLE TABLE (back table) ===========================
    
    // Pedestal - metallic
    glColor3f(0.78f, 0.78f, 0.80f);
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, offset);
        glVertex2f(0.05f, offset);
        glVertex2f(0.05f, offset + 0.45f);
        glVertex2f(-0.05f, offset + 0.45f);
    glEnd();
    
    // Table top rim (darker edge)
    glColor3f(0.28f, 0.28f, 0.28f);
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
    
    // Table top surface (light gray)
    glColor3f(0.80f, 0.80f, 0.82f);
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
    
    //=================== BOOK (BLACK) =========================
    glColor3f(0.08f, 0.08f, 0.08f);  // Very dark gray/black
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
    
    // Book spine shadow
    glColor3f(0.05f, 0.05f, 0.05f);
    glBegin(GL_QUADS);
        glVertex2f(-rectWidth / 2 + rectOffsetX, rectOffsetY);
        glVertex2f(-rectWidth / 2 + rectOffsetX + 0.02f, rectOffsetY);
        glVertex2f(-rectWidth / 2 + rectOffsetX + 0.02f, rectOffsetY + rectHeight);
        glVertex2f(-rectWidth / 2 + rectOffsetX, rectOffsetY + rectHeight);
    glEnd();

    //============= OUTLET ON WALL (right side) =====================
    glColor3f(0.88f, 0.88f, 0.88f);  // Light gray outlet
    float outletWidth = 0.06f;
    float outletHeight = 0.09f;
    float outletY = ovalCenterY + radiusY + 0.2f;
    float outletX = 0.85f;

    glBegin(GL_QUADS);
        glVertex2f(-outletWidth / 2 + outletX, outletY);
        glVertex2f(outletWidth / 2 + outletX, outletY);
        glVertex2f(outletWidth / 2 + outletX, outletY + outletHeight);
        glVertex2f(-outletWidth / 2 + outletX, outletY + outletHeight);
    glEnd();
    
    // Outlet holes (darker)
    glColor3f(0.3f, 0.3f, 0.3f);
    float holeSize = 0.015f;
    glBegin(GL_QUADS);
        glVertex2f(outletX - 0.015f, outletY + 0.055f);
        glVertex2f(outletX - 0.015f + holeSize, outletY + 0.055f);
        glVertex2f(outletX - 0.015f + holeSize, outletY + 0.055f + holeSize);
        glVertex2f(outletX - 0.015f, outletY + 0.055f + holeSize);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(outletX + 0.0f, outletY + 0.055f);
        glVertex2f(outletX + 0.0f + holeSize, outletY + 0.055f);
        glVertex2f(outletX + 0.0f + holeSize, outletY + 0.055f + holeSize);
        glVertex2f(outletX + 0.0f, outletY + 0.055f + holeSize);
    glEnd();
    
    //============= SWITCH ON WALL (left of laptop) =====================
    glColor3f(0.92f, 0.92f, 0.92f);
    float switchWidth = 0.06f;
    float switchHeight = 0.09f;
    float switchY = ovalCenterY + radiusY - 0.3f;
    float switchX = -0.25f;

    glBegin(GL_QUADS);
        glVertex2f(-switchWidth / 2 + switchX, switchY);
        glVertex2f(switchWidth / 2 + switchX, switchY);
        glVertex2f(switchWidth / 2 + switchX, switchY + switchHeight);
        glVertex2f(-switchWidth / 2 + switchX, switchY + switchHeight);
    glEnd();
    
    // Switch toggle
    glColor3f(0.85f, 0.82f, 0.78f);
    glBegin(GL_QUADS);
        glVertex2f(switchX - 0.015f, switchY + 0.035f);
        glVertex2f(switchX + 0.015f, switchY + 0.035f);
        glVertex2f(switchX + 0.015f, switchY + 0.055f);
        glVertex2f(switchX - 0.015f, switchY + 0.055f);
    glEnd();
    
    //================ LAPTOP (SIDE VIEW) =====================
    // Coordinates for trapezoid (screen)
    float trapTopRightX = rectOffsetX - rectWidth / 2 - 0.05f;
    float trapTopLeftX = trapTopRightX - 0.15f;
    float trapBottomRightX = trapTopRightX + 0.05f;
    float trapBottomLeftX = trapTopLeftX - 0.05f;

    float trapTopY = ovalCenterY + radiusY + 0.01f;
    float trapBottomY = trapTopY - 0.08f;

    float vertices[4][2] = {
        {trapTopLeftX, trapTopY},
        {trapTopRightX, trapTopY},
        {trapBottomRightX, trapBottomY},
        {trapBottomLeftX, trapBottomY}
    };

    float centerX = (vertices[0][0] + vertices[1][0] + vertices[2][0] + vertices[3][0]) / 4.0f;
    float centerY = (vertices[0][1] + vertices[1][1] + vertices[2][1] + vertices[3][1]) / 4.0f;

    float shiftX = -0.15f;
    float shiftY = 0.12f;

    float rotatedVertices[4][2];
    for (int i = 0; i < 4; i++) {
        float x = vertices[i][0];
        float y = vertices[i][1];
        rotatedVertices[i][0] = centerX + (y - centerY) + shiftX;
        rotatedVertices[i][1] = centerY - (x - centerX) + shiftY;
    }
    
    // Draw base (keyboard part - parallelogram)
    float baseLeftX = rotatedVertices[3][0];
    float baseRightX = rotatedVertices[2][0];
    float baseY = (rotatedVertices[2][1] + rotatedVertices[3][1]) / 2.0f;

    float shiftDown = 0.07f;
    float topLength = 0.15f;
    float bottomLength = 0.25f;
    float height = 0.07f;

    float baseCenterX = (baseLeftX + baseRightX) / 2.0f;

    float bottomTrapTopLeftX = baseCenterX - topLength / 2.0f;
    float bottomTrapTopRightX = baseCenterX + topLength / 2.0f;
    float bottomTrapTopY = baseY - shiftDown;

    float bottomTrapBottomLeftX = bottomTrapTopLeftX - (bottomLength - topLength) / 2.0f;
    float bottomTrapBottomRightX = bottomTrapTopRightX - (bottomLength - topLength) / 2.0f;
    float bottomTrapBottomY = bottomTrapTopY - height;

    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
        glVertex2f(bottomTrapTopLeftX, bottomTrapTopY);
        glVertex2f(bottomTrapTopRightX, bottomTrapTopY);
        glVertex2f(bottomTrapTopRightX, bottomTrapBottomY);
        glVertex2f(bottomTrapBottomLeftX, bottomTrapBottomY);
    glEnd();

    //Draw screen straight skinny rectangle)
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
        glVertex2f(rotatedVertices[0][0], rotatedVertices[0][1]);
        glVertex2f(rotatedVertices[1][0], rotatedVertices[1][1]);
        glVertex2f(rotatedVertices[2][0], rotatedVertices[2][1]);
        glVertex2f(rotatedVertices[3][0], rotatedVertices[3][1]);
    glEnd();

    // // Hinge (thin black rectangle)
    // float rectHeight2 = 0.015f;
    // float rectLeftX = bottomTrapBottomLeftX;
    // float rectRightX = bottomTrapBottomRightX;
    // float rectTopY = bottomTrapBottomY;
    // float rectBottomY = rectTopY - rectHeight2;

    // glColor3f(0.0f, 0.0f, 0.0f);
    // glBegin(GL_POLYGON);
    //     glVertex2f(rectLeftX, rectTopY);
    //     glVertex2f(rectRightX, rectTopY);
    //     glVertex2f(rectRightX, rectBottomY);
    //     glVertex2f(rectLeftX, rectBottomY);
    // glEnd();
      
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    float moveSpeed = 0.1f / zoomLevel;
    
    switch(key) {
        case 'w': case 'W':
            cameraY -= moveSpeed;
            if (cameraY > MAX_Y) cameraY = MAX_Y;
            break;
        case 's': case 'S':
            cameraY += moveSpeed;
            if (cameraY < MIN_Y) cameraY = MIN_Y;
            break;
        case 'a': case 'A':
            cameraX += moveSpeed;
            if (cameraX < MIN_X) cameraX = MIN_X;
            break;
        case 'd': case 'D':
            cameraX -= moveSpeed;
            if (cameraX > MAX_X) cameraX = MAX_X;
            break;
        case 'q': case 'Q':
            zoomLevel *= 1.1f;
            break;
        case 'e': case 'E':
            zoomLevel /= 1.1f;
            if (zoomLevel < 0.1f) zoomLevel = 0.1f;
            break;
        case 'r': case 'R':
            cameraX = 0.0f;
            cameraY = 0.0f;
            zoomLevel = 1.0f;
            break;
        case 27:
            exit(0);
            break;
    }
    
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 400);
    glutCreateWindow("Study Room Scene - WASD to move, QE to zoom, R to reset");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glutMainLoop();
    return 0;
}