cbuffer cb
{
	float4 faceRGB[8];
};

float4 main(uint id : SV_PrimitiveID) : SV_TARGET
{
	return faceRGB[(id / 2) % 8];
}