#include <GL/glut.h>
#include <cmath> 

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    //============ BACKGROUND ================================
    
    // Draw the upper half light gray
    glColor3f(0.7f, 0.7f, 0.7f);  // Light gray color
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, 0.0f);   // top left of upper half
        glVertex2f(1.0f, 0.0f);    // top right of upper half
        glVertex2f(1.0f, 1.0f);    // bottom right of upper half
        glVertex2f(-1.0f, 1.0f);   // bottom left of upper half
    glEnd();
    
    // Draw the lower half light brown
    glColor3f(0.885f, 0.84f, 0.64f);   // Light brown color
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);   // top left of lower half
        glVertex2f(1.0f, -1.0f);    // top right of lower half
        glVertex2f(1.0f, 0.0f);     // bottom right of lower half
        glVertex2f(-1.0f, 0.0f);    // bottom left of lower half
    glEnd();
    
    // Add a slightly darker thin rectangle on the yellow-brown side (flush with the center)
    glColor3f(0.75f, 0.7f, 0.5f);  // Slightly darker brown with a touch of yellow
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, 0.05f);   // top left of the rectangle
        glVertex2f(1.0f, 0.05f);    // top right of the rectangle
        glVertex2f(1.0f, -0.05f);   // bottom right of the rectangle
        glVertex2f(-1.0f, -0.05f);  // bottom left of the rectangle
    glEnd();
    
    
    //====================== RECTANGLE TABLE ==============================
    
    // Move table up further to the bottom half of the scene
    float offset = -0.15f; // The new vertical offset to move the table up more
   
    // Draw the trapezoid (table top) - now with a smaller top width than the bottom
    glColor3f(0.82f, 0.71f, 0.55f);  // tan color for trapezoid
    glBegin(GL_POLYGON);
        glVertex2f(-0.7f, offset);    // top left (smaller than bottom)
        glVertex2f(0.7f, offset);     // top right (smaller than bottom)
        glVertex2f(0.9f, offset - 0.3f);   // bottom right
        glVertex2f(-0.9f, offset - 0.3f);  // bottom left
    glEnd();
    
    // Draw rectangle (tan) below trapezoid (table body) - now aligned with trapezoid sides
    glColor3f(0.69f, 0.58f, 0.43f);  // tan color for the table body
    glBegin(GL_QUADS);
        glVertex2f(-0.9f, offset - 0.3f);    // top left of rect (same as trapezoid bottom left)
        glVertex2f(0.9f, offset - 0.3f);     // top right of rect (same as trapezoid bottom right)
        glVertex2f(0.9f, offset - 0.7f);     // bottom right of rect (lowered)
        glVertex2f(-0.9f, offset - 0.7f);    // bottom left of rect (lowered)
    glEnd();
    
    // Draw inner rectangle (darker tan) inside the first rectangle (table inner surface)
    glColor3f(0.55f, 0.45f, 0.3f); // Darker tan color for inner rectangle
    glBegin(GL_QUADS);
        glVertex2f(-0.8f, offset - 0.35f);  // top left of inner rectangle (scaled inward)
        glVertex2f(0.8f, offset - 0.35f);   // top right of inner rectangle (scaled inward)
        glVertex2f(0.8f, offset - 0.65f);   // bottom right of inner rectangle (scaled inward)
        glVertex2f(-0.8f, offset - 0.65f);  // bottom left of inner rectangle (scaled inward)
    glEnd();
    
    // Legs
    glColor3f(0.5f, 0.5f, 0.5f);  // Gray color for the legs

    // Left leg (same size, moved inward slightly, but brought down a little)
    glBegin(GL_QUADS);
        glVertex2f(-0.80f, offset - 0.7f);   // top left (flush with outer rectangle)
        glVertex2f(-0.66f, offset - 0.7f);   // top right (flush with outer rectangle)
        glVertex2f(-0.66f, offset - 0.82f);  // bottom right (slightly lower)
        glVertex2f(-0.80f, offset - 0.82f);  // bottom left (slightly lower)
    glEnd();

    // Right leg (same size, moved inward slightly, but brought down a little)
    glBegin(GL_QUADS);
        glVertex2f(0.66f, offset - 0.7f);    // top left (flush with outer rectangle)
        glVertex2f(0.80f, offset - 0.7f);    // top right (flush with outer rectangle)
        glVertex2f(0.80f, offset - 0.82f);   // bottom right (slightly lower)
        glVertex2f(0.66f, offset - 0.82f);   // bottom left (slightly lower)
    glEnd();
    
    //================= PILLOW1 =====================
    
    
     // Dark blue color 
    glColor3f(0.0f, 0.0f, 0.5f);  // Dark blue
    
    
    
    //==================== CIRCLE TABLE ===========================
    
    // Add thin light gray rectangle at the top of the trapezoid (centered horizontally)
    glColor3f(0.75f, 0.75f, 0.75f);  // Light gray color
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, offset);         // top left (centered on the short side of the trapezoid)
        glVertex2f(0.05f, offset);          // top right (centered on the short side of the trapezoid)
        glVertex2f(0.05f, offset + 0.45f);  // bottom right (three times the height)
        glVertex2f(-0.05f, offset + 0.45f); // bottom left (three times the height)
    glEnd();
    
    //table top circle rim
    
    // Add oval positioned at the top of the rectangle
    glColor3f(0.33f, 0.33f, 0.33f);  // Red color
    int numSegments = 100;  // Number of segments to approximate the oval
    float radiusX = 0.55f;   // Horizontal radius (same as before)
    float radiusY = 0.07f;   // Slightly increased vertical radius for more height

    // Oval's center should be at the top of the rectangle, just above it
    float ovalCenterY = offset + 0.45f + radiusY;

    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++) {
        float angle = 2.0f * 3.14159f * i / numSegments;
        float x = radiusX * cos(angle); // X-coordinate of the oval
        float y = radiusY * sin(angle); // Y-coordinate of the oval
        glVertex2f(x, ovalCenterY + y); // Position around the rectangle center
    }
    glEnd();
    
    // table top circle
    
    // Add oval inside the dark gray oval (with smaller vertical radius)
    glColor3f(0.83f, 0.83f, 0.83f); // Red color
    float innerRadiusX = 0.52f;    // Slightly smaller horizontal radius to bring the sides in
    float innerRadiusY = 0.05f;    // Slightly smaller vertical radius to make it shorter

    // Adjust the Y-position to move the red oval down slightly inside the gray oval
    float redOvalOffset = 0.02f;  // Increased offset to move the red oval down

    // Draw oval inside the dark gray oval
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++) {
        float angle = 2.0f * 3.14159f * i / numSegments;
        float x = innerRadiusX * cos(angle); // X-coordinate of the inner oval
        float y = innerRadiusY * sin(angle); // Y-coordinate of the inner oval
        glVertex2f(x, ovalCenterY + y + redOvalOffset); // Adjusted Y to move it down inside
    }
    glEnd();
    
    //=================== BOOK =========================
    
    // Black rectangle on top of the light gray oval
    glColor3f(0.0f, 0.0f, 0.0f);  // Black color for the rectangle

    // Define rectangle position and size
    float rectWidth = 0.22f;   // Width of the rectangle
    float rectHeight = 0.28f;  // Height of the rectangle

    // Move the rectangle down slightly by reducing the Y-position
    float rectOffsetY = ovalCenterY + radiusY - 0.05f;  // Move it down slightly

    // Move the rectangle to the left by adjusting the X-position
    float rectOffsetX = 0.25f;  // Move the rectangle to the left (negative value)

    glBegin(GL_QUADS);
        glVertex2f(-rectWidth / 2 + rectOffsetX, rectOffsetY);  // Top left
        glVertex2f(rectWidth / 2 + rectOffsetX, rectOffsetY);   // Top right
        glVertex2f(rectWidth / 2 + rectOffsetX, rectOffsetY + rectHeight); // Bottom right
        glVertex2f(-rectWidth / 2 + rectOffsetX, rectOffsetY + rectHeight); // Bottom left
    glEnd();

    //============= SWITCH =====================
    // White rectangle 
    glColor3f(1.0f, 1.0f, 1.0f);  // Black color for the rectangle

    // Define rectangle position and size
    float SWrectWidth = 0.06f;   // Width of the rectangle
    float SWrectHeight = 0.09f;  // Height of the rectangle

    // Move the rectangle down slightly by reducing the Y-position
    float SWrectOffsetY = ovalCenterY + radiusY - 0.3f;  // Move it down slightly

    // Move the rectangle to the left by adjusting the X-position
    float SWrectOffsetX = -0.25f;  // Move the rectangle to the left (negative value)

    glBegin(GL_QUADS);
        glVertex2f(-SWrectWidth / 2 + SWrectOffsetX, SWrectOffsetY);  // Top left
        glVertex2f(SWrectWidth / 2 + SWrectOffsetX, SWrectOffsetY);   // Top right
        glVertex2f(SWrectWidth / 2 + SWrectOffsetX, SWrectOffsetY + SWrectHeight); // Bottom right
        glVertex2f(-SWrectWidth / 2 + SWrectOffsetX, SWrectOffsetY + SWrectHeight); // Bottom left
    glEnd();
    //============== SOCKET =====================
    // White rectangle 
    glColor3f(1.0f, 1.0f, 1.0f);  // Black color for the rectangle

    // Define rectangle position and size
    float LrectWidth = 0.05f;   // Width of the rectangle
    float LrectHeight = 0.08f;  // Height of the rectangle

    // Move the rectangle down slightly by reducing the Y-position
    float LrectOffsetY = ovalCenterY + radiusY + 0.2f;  // Move it down slightly

    // Move the rectangle to the left by adjusting the X-position
    float LrectOffsetX = 0.85f;  // Move the rectangle to the left (negative value)

    glBegin(GL_QUADS);
        glVertex2f(-LrectWidth / 2 + LrectOffsetX, LrectOffsetY);  // Top left
        glVertex2f(LrectWidth / 2 + LrectOffsetX, LrectOffsetY);   // Top right
        glVertex2f(LrectWidth / 2 + LrectOffsetX, LrectOffsetY + LrectHeight); // Bottom right
        glVertex2f(-LrectWidth / 2 + LrectOffsetX, LrectOffsetY + LrectHeight); // Bottom left
    glEnd();
    //================ LAPTOP =====================
    
  
    //=================== CHAIR1 ========================
    
    //==================== PILLOW2 =========================
    
    //===================== CHAIR2 =======================
    glFlush();
}
/*
void reshape(int w, int h) {
    glViewport(0, 0, w, h);  // viewport covers whole window

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Fixed orthographic projection bounds (matches your shape coords roughly)
    // Adjust as needed to see entire shape clearly
    if (w <= h)
        gluOrtho2D(-1.0, 1.0, -1.0 * (GLfloat)h / (GLfloat)w, 1.0 * (GLfloat)h / (GLfloat)w);
    else
        gluOrtho2D(-1.0 * (GLfloat)w / (GLfloat)h, 1.0 * (GLfloat)w / (GLfloat)h, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}*/


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Scene");
    glutInitWindowSize(800, 400);
    glutDisplayFunc(display);

    
    //glutReshapeFunc(reshape);
    
    // Set background color to white
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glutMainLoop();
    return 0;
    
}

