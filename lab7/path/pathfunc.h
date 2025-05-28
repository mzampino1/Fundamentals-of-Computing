// declaration of Point struct
typedef struct {
	float x;
	float y;
} Point;

// function prototypes
FILE* openUserFile();
int assignFilePoints(Point points[], FILE* fp);
float calcDistance(Point p1, Point p2);
float calcPathLength(Point points[], int numPoints);
void printPointInfo(Point points[], int numPoints, float pathLength);
