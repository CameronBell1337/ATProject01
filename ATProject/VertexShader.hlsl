cbuffer cb
{
	matrix transform;

};

struct VSOut
{
	float4 colour : Colour;
	float4 pos : SV_Position;
};

VSOut main(float3 pos : POSITION, float4 colour : Colour)
{
	VSOut _vso;
	_vso.pos = mul(float4(pos, 1.0f), transform);
	_vso.colour = colour;
	return _vso;
}