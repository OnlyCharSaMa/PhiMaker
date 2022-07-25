function beatToReal(beat, BPM)
{
    return beat / BPM * 60 * 1000;
}

function realToBeat(real, BPM)
{
    return real / 60 / 1000 * BPM;
}
